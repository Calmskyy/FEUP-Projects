@extends('layouts.app')

@section('pageTitle', 'Sell your item')

@section('cssImports')
<link href="{{ asset('css/item_sell.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
<script type="text/javascript" src="{{ asset('js/item_sell_page.js') }}" defer></script>
@endsection

@section('content')
    
<div class="signup-container">
    <div class="d-flex justify-content-center h-100">
      <div class="card">
        <h1>Sell Item</h1>
        <form method="POST" enctype="multipart/form-data" action="{{ route('item_create') }}">
            {{ csrf_field() }}
          <div class="form-group">
            <h2>*Option</h2>
                <select id="sell-type-select" name="sell-type" onChange="changeSellType(this)" required>
                    <option value="Sale">Put up for Sale</option>
                    <option value="Auction">Put up for Auction</option>
                </select>
          </div>
          <div class="form-group">
            <h2>*Item Name</h2>
            <input type="text" name="title" class="form-control" value="" required/>
          </div>
          <div class="form-group two-division numeric">
            <div class="form-group start-bid">
              <h2 id="price-label">*Price</h2>
              <input type="number" name="price" class="form-control" value="" placeholder="EUR" required/>
            </div>
            <div id="difference-form-group" class="form-group difference" hidden>
              <h2>Difference between bids</h2>
              <input id="difference-input" type="number" name="difference" class="form-control" value="" placeholder="EUR"/>
            </div>
          </div>
          <div id="dates-form-group" class="form-group two-division" hidden>
              <div class="date">
                <h2>Limit Date</h2>
                <input id="limit-date-input" type="date" name="limit_date" class="form-control" value="" />
              </div>
              <div class="time">
                <h2>Limit Hour</h2>
                <input id="limit-hour-input" type="time" name="limit_hour" class="form-control" value="" />
              </div>
          </div>
          <div class="form-group Category">
            <h2>*Category</h2>
            <select name="category" required>
                <option value="">Select</option>
                <option value="Painting">Painting</option>
                <option value="Sculpture">Sculpture</option>
                <option value="Photography">Photography</option>
                <option value="Drawing">Drawing</option>               
                <option value="Serigraphy">Serigraphy</option>
                <option value="Ceramics">Ceramics</option>
            </select>
          </div>
          <div class="form-group description">
            <h2>*Description</h2>
            <textarea type="text" name="description" class="form-control" value="" cols="90" rows="5" required></textarea>
          </div>
          <div class="form-group description">
            <div class="form-group">
                <label for="imageInput">*Upload images</label>
                <input required type="file" class="form-control" data-preview="#preview" name="images[]" id="imageInput" multiple>
                <img class="col-sm-6" id="preview"  src="">
            </div>

          </div>
          <div class="form-group">
            <input type="submit" class="btnSubmit" value="Submit" />
          </div>
        </form>
      </div>
    </div>

@endsection
