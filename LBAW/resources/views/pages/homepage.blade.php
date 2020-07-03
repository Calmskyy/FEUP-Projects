@extends('layouts.app')

@section('pageTitle', 'artBay')

@section('cssImports')

<link href="{{ asset('css/homepage.css') }}" rel="stylesheet">

@endsection

@section('content')


    <div class="container-fluid">

    <br>

    <div class="row">
      <div class="col">
        <div class="row">
          <div class="col mx-4 mt-4">
            <div class="mt-3 mx-2">
              <h3>Current Auctions</h3>
            </div>
          </div>
        </div>

        <div class="row">
          <div class="col mx-4 mt-2 slider-items">
            <div class="py-3 slider">
              @foreach($itemAuction as $item_auction)
                <div class="mr-1"> 
                @if (count($item_auction->item->imagesItem) > 0)
                  <a href="{{'./item/' . $item_auction->item['id']}}"><img src="{{asset('/images/items/' . $item_auction->item->imagesItem[0]->image['url'])}}" height="250" width="250" class="img-responsive"></a>
                @else
                  <a href="{{'./item/' . $item_auction->item['id']}}"><img src="{{asset('/images/items/default.jpg')}}" height="250" width="250" class="img-responsive"></a>
                @endif
                </div>
              @endforeach
            </div>
          </div>
        </div>

      </div>
    </div>

    <br>
    <hr>
    <br>

    <div class="row">
      <div class="col">
        <div class="row">
          <div class="col mx-4 mt-4">
            <div class="mt-3 mx-2">
              <h3>Current Sales</h3>
            </div>
          </div>
        </div>

        <div class="row">
          <div class="col mx-4 mt-2 slider-items">
            <div class="py-3 slider">
              @foreach($itemPurchase as $item_purchase)
                <div class="mr-1"> 
                @if (count($item_purchase->item->imagesItem) > 0)
                  <a href="{{'./item/' . $item_purchase->item['id']}}"><img src="{{asset('/images/items/' . $item_purchase->item->imagesItem[0]->image['url'])}}" height="250" width="250" class="img-responsive"></a>
                @else
                  <a href="{{'./item/' . $item_purchase->item['id']}}"><img src="{{asset('/images/items/default.jpg')}}" height="250" width="250" class="img-responsive"></a>
                @endif
                </div>
              @endforeach
            </div>
          </div>
        </div>


      </div>
    </div>

    <br>
    <hr>
    <br>


    <!-- <footer class="row">
      <div class="col bg-warning">
        <div class="d-flex justify-content-center pt-4">
          <img class="mx-4" width="40" height="40" src="facebook.png" alt="facebook link">
          <img class="mx-4" width="40" height="40" src="instagram.png" alt="instagram link">
          <img class="mx-4" width="40" height="40" src="linkedin.png" alt="linkedin link">
        </div>
        <div class="float-right py-1 pr-3">
          <p>Copyright artbay 2020</p>
        </div>
      </div>
  </footer> -->

  </div>
@endsection