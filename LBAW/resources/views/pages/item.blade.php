@extends('layouts.app')

@section('pageTitle', $item->title)

@section('cssImports')

<link href="{{ asset('css/itempage.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
<script type="text/javascript" src="{{ URL::asset('js/itempage.js') }}" defer></script>
@endsection

@section('content')

<div class="card">
    <div class="row">
        <div class="col mt-4">
            <div class="images">
            @foreach($item->imagesItem as $imageItem)
                <div class="image-square"><img src="{{asset('/images/items/' . $imageItem->image['url'])}}" alt="arte"/></div>
            @endforeach
            </div>
            <div class="foto">
                @if (count($item->imagesItem) > 0)
                    <img id="image-principal" src="{{asset('/images/items/' . $item->imagesItem[0]->image['url'])}}" alt="arte"></img>
                @else
                    <img id="image-principal" src="{{asset('/images/items/default.jpg')}}" alt="arte"></img>
                @endif
                <div id="sellerInfo">
                    @if (!is_null($item->owner->imageUser))
                        <img id="avatar" src="{{asset('/images/users/' . $item->owner->imageUser->image['url'])}}" alt="User's avatar"></img>
                    @else
                        <img id="avatar" src="{{asset('/images/users/default.png')}}" alt="User's avatar"></img>
                    @endif
                    <div>
                        <h1>{{ $item->owner['name'] }}</h1>
                        @for ($i = 0; $i < $item->owner['reputation']; $i++)
                            <span class="fa fa-star checked"></span>
                        @endfor
                        @for (; $i < 5; $i++)
                            <span class="fa fa-star"></span>
                        @endfor
                    </div>
                </div>
            </div>
            <div class="text">
                <h1>{{ $item->title }}</h1>
                @can('update', $item)
                    <a class="btn" href="{{ route('item_edit', $item->id) }}">Edit Item</a>
                @endcan
                @can('delete', $item)
                <form action="{{ route('item_remove', $item->id) }}" method="POST">
                    <input type="hidden" name="_method" value="DELETE">
                    <input type="hidden" name="_token" value="{{ csrf_token() }}">
                    <input class="btn" type="submit" value="Delete">
                </form>
                @endcan
                @if (!is_null(Auth::user()) && Auth::user()['is_admin'])
                    <!-- Button trigger modal -->
                    <button type="button" class="btn btn-danger" data-toggle="modal" data-target="#stopSale">
                    Stop sale
                    </button>

                    <!-- Modal -->
                    <div class="modal fade" id="stopSale" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
                        <div class="modal-dialog modal-dialog-centered" role="document">
                            <div class="modal-content">
                                <form method="POST" action="{{ route('item_stop', $item->id) }}">
                                    {{ csrf_field() }}
                                    <div class="modal-header">
                                        <h5 class="modal-title" id="exampleModalLabel">Reason for stopping sale</h5>
                                        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                        <span aria-hidden="true">&times;</span>
                                        </button>
                                    </div>
                                    <div class="modal-body">
                                        <textarea name="reason" placeholder="Reason..." type="textarea"></textarea>
                                    </div>
                                    <div class="modal-footer">
                                        <button type="button" class="btn btn-secondary" data-dismiss="modal">Cancel</button>
                                        <button type="submit" class="btn btn-danger">Submit</button>
                                    </div>
                                </form>
                            </div>
                        </div>
                    </div>
                @endif
                @if (!is_null($itemAuction))
                
                    @if((strtotime($itemAuction->end_time) < strtotime(date("Y-m-d H:i:s" . " -0100"))) && !Auth::guest() && ($item->seller_id == Auth::user()->id))
                    <form action="/endauction" method="POST">
                        <input type="hidden" name="_token" value="{{ csrf_token() }}">
                        <input type="hidden" name="seller_id" value="{{ Auth::user()->id }}">
                        <input type="hidden" name="last_bid" value="{{ $itemAuction->current_bid }}">
                        <input type="hidden" name="item_id" value="{{ $itemAuction->item_id }}">
                        <input class="btn" type="submit" value="Finish auction">
                    </form>               
                    @endif
                    
                    <p>Starting Bid: {{ $itemAuction->starting_bid }}€</p>
                    <p id="countdown"></p>
                    <script>
                        var countDownDate = new Date("{{ $itemAuction->end_time}}").getTime();

                        var x = setInterval(function() {
                            var now = new Date().getTime();

                            var distance = countDownDate - now;

                            var days = Math.floor(distance / (1000 * 60 * 60 * 24));
                            var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
                            var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
                            var seconds = Math.floor((distance % (1000 * 60)) / 1000);

                            document.getElementById("countdown").innerHTML = days + "d " + hours + "h "
                            + minutes + "m " + seconds + "s ";

                            if (distance < 0) {
                                clearInterval(x);
                                document.getElementById("countdown").innerHTML = "CONCLUDED";
                            }

                        }, 1000);
                    </script>
                    <p>Limit Date: <strong>{{ $itemAuction->end_time->format('d/m/Y H:i:s') }}</strong></p>
                    <p>Current bid: <strong>{{ !is_null($itemAuction->current_bid) ? $itemAuction->current_bid : "---" }}€</strong></p>
                    <p id="bidder">[{{ !is_null($itemAuction->current_bid)? "Unknown user" : "No bids"}}]</p>
                    @can('pay', $item)
                    @if((strtotime($itemAuction->end_time) > strtotime(date("Y-m-d H:i:s" . " -0100"))) && !Auth::guest() && Auth::user()->cash >= $itemAuction->current_bid)
                    <div id="input">
                        <form method="POST" id="payment-form" action="/bid">
                            <input type="hidden" name="_token" value="{{ csrf_token() }}">
                            <input type="hidden" name="item_id" value="{{ $item->id }}">
                            <input type="hidden" name="bidder_id" value="{{ Auth::user()->id }}">
                            <input type="number" min="{{ $itemAuction->current_bid+$itemAuction->bid_difference }}" name="amount" placeholder="EUR" required/>
                            <button id="btn" class="btn">BID</button>
                            <p>Minimum bid amount allowed</p>
                            @if (!is_null($itemAuction->current_bid))
                                <p>€{{ $itemAuction->current_bid+$itemAuction->bid_difference }}</p>
                            @else
                                <p>€{{ $itemAuction->starting_bid }}</p>
                            @endif
                        </form>
                    </div>
                    @endif
                    @endcan
                @endif

                @if (!is_null($itemPurchase))
                    <h1>Price: {{ $itemPurchase->price }}€</h1>
                    @can('pay', $item)
                    @if($itemPurchase->price <= Auth::user()->cash)
                    <form method="POST" id="payment-form" action="/itempurchase">
                        <input type="hidden" name="_token" value="{{ csrf_token() }}">
                        <input type="hidden" name="item_id" value="{{ $item->id }}">
                        <input type="hidden" name="price" value="{{ $itemPurchase->price }}">
                        <input type="hidden" name="buyer_id" value="{{ Auth::user()->id }}">
                        <input type="hidden" name="seller_id" value="{{ $item->seller_id }}">
                        <button id="btn" class="btn">BUY</button>
                    </form>
                    @endif
                    @endcan
                @endif

                @if ($item['stopped'])
                    <h1>STOPPED ITEM SALE</h1>
                @endif


                <h2>Description</h2>
                <p>{{ $item->description }}</p>
                <h2>Comments</h2>
                <div class="comments">
                    @if (!is_null($comments))
                      @for ($i = 0; $i < count($comments); $i++)
                        <div class="comment">
                            @if ($comments[$i]['deleted'])
                                @if (!is_null($comments[$i]->user->imageUser))
                                    <img class="comment-avatar" src="{{asset('/images/users/' . $comments[$i]->user->imageUser->image['url'])}}" alt="User's avatar"></img>
                                @else
                                    <img class="comment-avatar" src="{{asset('/images/users/default.png')}}" alt="User's avatar"></img>
                                @endif
                                <h1>{{ $comments[$i]->user['name'] }}</h1><i class="date">{{ $comments[$i]->date }}</i>
                                <i class="deleted">This comment has been deleted.</i>
                                </div>
                                @continue
                            @endif
                            @if (!is_null($comments[$i]->user->imageUser))
                                <img class="comment-avatar" src="{{asset('/images/users/' . $comments[$i]->user->imageUser->image['url'])}}" alt="User's avatar"></img>
                            @else
                                <img class="comment-avatar" src="{{asset('/images/users/default.png')}}" alt="User's avatar"></img>
                            @endif
                            <h1>{{ $comments[$i]->user['name'] }}</h1><i class="date">{{ $comments[$i]->date }}</i>
                            <p contentEditable=false>{{ $comments[$i]->content }}</p>
                            @if (!is_null(Auth::user()) && Auth::user()['is_admin'])
                                <!-- Button trigger modal -->
                                <button type="button" style="margin-top: 0.25em" class="btn btn-danger" data-toggle="modal" data-target="#modComment{{$comments[$i]->id}}">
                                Mod Delete Comment
                                </button>

                                <!-- Modal -->
                                <div class="modal fade" id="modComment{{$comments[$i]->id}}" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
                                    <div class="modal-dialog modal-dialog-centered" role="document">
                                        <div class="modal-content">
                                            <form method="POST" action="{{ route('comment_mod_delete', $comments[$i]->id) }}">
                                                {{ csrf_field() }}
                                                <div class="modal-header">
                                                    <h5 class="modal-title" id="exampleModalLabel">Reason for deleting comment</h5>
                                                    <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                                                    <span aria-hidden="true">&times;</span>
                                                    </button>
                                                </div>
                                                <div class="modal-body">
                                                    <textarea name="reason" placeholder="Reason..." type="textarea"></textarea>
                                                </div>
                                                <div class="modal-footer">
                                                    <button type="button" class="btn btn-secondary" data-dismiss="modal">Cancel</button>
                                                    <button type="submit" class="btn btn-danger">Submit</button>
                                                </div>
                                            </form>
                                        </div>
                                    </div>
                                </div>
                            @endif
                            @can('update', $comments[$i])
                                <button type="button" class="btn edit_comment">Edit Comment</button>
                                <button type="button" class="btn delete_comment">Delete Comment</button>
                            @endcan
                            <form method="POST" display="none" action="{{ route('comment_edit', $comments[$i]->id) }}">
                                {{ csrf_field() }}
                                <input type="hidden" name="content" value="test">
                                <button type="submit" style="display: none">Edit Comment</button>
                            </form>
                            <form method="POST" display="none" action="{{ route('comment_delete', $comments[$i]->id) }}">
                                {{ csrf_field() }}
                                <button type="submit" style="display: none">Delete Comment</button>
                            </form>
                        </div>                      
                      @endfor
                      @if (count($comments) == 0)
                        <i>(No comments have been made yet.)</i>
                      @endif
                      @if (!is_null(Auth::user()) && !Auth::user()['is_admin'] )
                        <div class="comment" id="newComment">
                        <button type="button" class="btn create_comment">Create Comment</button>
                        @if (!is_null(Auth::user()->imageUser))
                            <img class="comment-avatar" src="{{asset('/images/users/' . Auth::user()->imageUser->image['url'])}}" alt="User's avatar"></img>
                        @else
                            <img class="comment-avatar" src="{{asset('/images/users/default.png')}}" alt="User's avatar"></img>
                        @endif
                        <h1>{{ Auth::user()['name'] }}</h1>
                        <p data-placeholder="Type your comment here..." contentEditable=true></p>
                        <form method="POST" display="none" action="{{ route('comment_insert') }}">
                            {{ csrf_field() }}
                            <input type="hidden" name="user_id" value="{{ Auth::user()['id'] }}">
                            <input type="hidden" name="item_id" value="{{ $item->id }}">
                            <input type="hidden" name="content" value="test">
                            <button type="submit" style="display: none">Post Comment</button>
                        </form>
                        </div>
                       @endif
                    @endif
                </div>      
            </div>
        </div>
    </div>
</div>


@endsection