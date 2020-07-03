@extends('layouts.app')

@section('pageTitle', $item->title)

@section('cssImports')

<link href="{{ asset('css/itempage.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
@endsection

@section('content')

<div class="card">
    <div class="row">
        <div class="col mt-4">
            <div class="images">
            @foreach($item->imagesItem as $imageItem)
                <div class="image-square"><img src="{{asset('/images/items/' . $imageItem->image['url'])}}"/></div>
            @endforeach
            </div>
            <div class="foto">
                @if (count($item->imagesItem) > 0)
                    <img id="image" src="{{asset('/images/items/' . $item->imagesItem[0]->image['url'])}}" alt="arte"></img>
                @else
                    <img id="image" src="{{asset('/images/items/default.jpg')}}" alt="arte"></img>
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
            <form method="POST" enctype="multipart/form-data" action="{{ route('item_edit', $item->id) }}">
            {{ csrf_field() }}
            <div class="text">
            <h2>*Title</h2>
                <input name="title" type="text" value="{{ $item->title }}" required>

                @if (!is_null($itemAuction))
                    <p>Starting Bid: {{ $itemAuction->starting_bid }}€</p>
                    <table>
                        <th colspan="4">Time Left</th>
                        <tr>
                            <td id="days">--d</td>
                            <td id="hours">--h</td>
                            <td id="minutes">--m</td>
                            <td id="seconds">--s</td>
                        </tr>
                    </table>
                    <p>Limit Date: <strong>{{ $itemAuction->end_time->format('d/m/Y H:i:s') }}</strong></p>
                    <p>Current bid: <strong>{{ !is_null($itemAuction->current_bid) ? $itemAuction->current_bid : "---" }}€</strong></p>
                    <p id="bidder">[{{ !is_null($itemAuction->current_bid)? "Unknown user" : "No bids"}}]</p>
                @endif

                @if (!is_null($itemPurchase))
                    <h1>Price: {{ $itemPurchase->price }}€</h1>
                @endif


                <h2>*Description</h2>
                <input name="description" type="text" value="{{ $item->description }}" required>
                <div class="form-group">
                    <label for="imageInput">Replace images</label>
                    <input type="file" class="form-control" data-preview="#preview" name="images[]" id="imageInput" multiple>
                    <img class="col-sm-6" id="preview"  src="">
                </div>
                <button type="submit" style="display:block" class="btn btn-primary">Update</button>
            </div>
            </form>
        </div>
    </div>
</div>


@endsection