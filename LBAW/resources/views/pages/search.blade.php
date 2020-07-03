@extends('layouts.app')

@section('pageTitle', 'Search results')

@section('cssImports')
<link href="{{ asset('css/search.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
<script type="text/javascript" src="{{ URL::asset('js/searchpage.js') }}" defer></script>
@endsection

@section('content')

<div class="row pt-4">

    <div class="col-12 col-sm-4 col-lg-2">

        <h5>Categories:</h5>
        <ul class="list-unstyled list-filters">
            <li><a class="category-link {{($category == "Painting")? "selected" : ""}}" href="#">Painting</a></li>
            <li><a class="category-link {{($category == "Sculpture")? "selected" : ""}}" href="#">Sculpture</a></li>
            <li><a class="category-link {{($category == "Photography")? "selected" : ""}}" href="#">Photography</a></li>
            <li><a class="category-link {{($category == "Drawing")? "selected" : ""}}" href="#">Drawing</a></li>
            <li><a class="category-link {{($category == "Serigraphy")? "selected" : ""}}" href="#">Serigraphy</a></li>
            <li><a class="category-link {{($category == "Ceramics")? "selected" : ""}}" href="#">Ceramics</a></li>
        </ul>

    </div>

    <div class="col">
        <h5> Results for <b> {{ (($category == "")? "All" : $category) . " " . $query }} </b> :</h5>

        <!-- @foreach($details as $user)
            <div>{{$user->id}}</div>
        @endforeach -->

        @foreach($itemAuction as $auction)
            @foreach($details as $item)
                @if ($item->id == $auction->item->getId())


                <div class="row search-item pt-3 px-3">
                    <div class="m-2 search-item-image">
                        @if (count($auction->item->imagesItem) > 0)
                            <a href="{{'./item/' . $auction->item['id']}}"><img src="{{asset('/images/items/' . $auction->item->imagesItem[0]->image['url'])}}" height="250" width="250" class="img-responsive"></a>
                        @else
                            <a href="{{'./item/' . $auction->item['id']}}"><img src="{{asset('/images/items/default.jpg')}}" height="250" width="250" class="img-responsive"></a>
                        @endif
                    </div>
                    <div class="col py-3">
                        <h4>{{ $auction->item['title']}}</h4>
                        <h5 class="search-item-description">{{$auction->item['description']}}</h5>
                        
                        <div class="my-4">
                        <span>Highest bid:</span>
                        <h5 class="my-1">{{ !is_null($auction->current_bid) ? $auction->current_bid : "---" }}$</h5>
                        </div>

                        <div class="my-4">
                            <h6>{{ $auction->item->owner['name'] }}</h6>
                            @for ($i = 0; $i < $auction->item->owner['reputation']; $i++)
                                <span class="fa fa-star checked"></span>
                            @endfor
                            @for (; $i < 5; $i++)
                                <span class="fa fa-star"></span>
                            @endfor
                            <span class="mx-1">{{$auction->item->owner['reputation']}}</span>
                        </div>
                        
                    </div>
                </div>

                <hr>

                @break
                @endif
            @endforeach
        @endforeach

        @foreach($itemPurchase as $purchase)
            @foreach($details as $item)
                @if ($item->id == $purchase->item->getId())


                <div class="row search-item pt-3 px-3">
                    <div class="m-2 search-item-image">
                        @if (count($purchase->item->imagesItem) > 0)
                            <a href="{{'./item/' . $purchase->item['id']}}"><img src="{{asset('/images/items/' . $purchase->item->imagesItem[0]->image['url'])}}" height="250" width="250" class="img-responsive"></a>
                        @else
                            <a href="{{'./item/' . $purchase->item['id']}}"><img src="{{asset('/images/items/default.jpg')}}" height="250" width="250" class="img-responsive"></a>
                        @endif
                    </div>
                    <div class="col py-3">
                        <h4>{{ $purchase->item['title']}}</h4>
                        <h5 class="search-item-description">{{$purchase->item['description']}}</h5>
                        
                        <div class="my-4">
                            <span>Price:</span>
                            <h5 class="my-1">{{ $purchase['price'] }}$</h5>
                        </div>

                        <div class="my-4">
                            <h6>{{ $purchase->item->owner['name'] }}</h6>
                            @for ($i = 0; $i < $purchase->item->owner['reputation']; $i++)
                                <span class="fa fa-star checked"></span>
                            @endfor
                            @for (; $i < 5; $i++)
                                <span class="fa fa-star"></span>
                            @endfor
                            <span class="mx-1">{{$purchase->item->owner['reputation']}}</span>
                        </div>
                        
                    </div>
                </div>

                <hr>

                @break
                @endif
            @endforeach
        @endforeach

        <!-- @each('partials.item_auction', $itemAuction, 'item_auction') -->
        <!-- @each('partials.item_purchase', $itemPurchase, 'item_purchase') -->

    </div>
</div>


</div>




@endsection
