@extends('layouts.app')

@section('pageTitle', 'Review ' . $title)

@section('cssImports')

<link href="{{ asset('css/review.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
@endsection

@section('content')


  <div class="container-fluid">

   <div class="row">
       <div class="col-12 text-center ">

            <div class="mt-4">
                <h2>Review seller:</h2>
                <a href="#"><img src="{{asset('/images/users/' . $seller->imageUser->image['url'])}}" height="200" width="200" class="img-responsive rounded-circle my-4"></a>
                <h3>{{$seller->name}}</h3>
                <div class="my-4">
                    <span class="fa fa-star fa-2x checked"></span>
                    <span class="fa fa-star fa-2x checked"></span>
                    <span class="fa fa-star fa-2x checked"></span>
                    <span class="fa fa-star fa-2x"></span>
                    <span class="fa fa-star fa-2x"></span>
                </div>
                <h3>{{$title}}</h3>
                <div class="form-group mx-auto">
                    <form action="/create" method="POST">
                        <input type="hidden" name="_token" value="{{ csrf_token() }}">
                        <input type="hidden" name="seller_name" value="{{$seller->name}}">
                        <input type="hidden" name="item_title" value="{{$title}}">
                        <input type="hidden" name="buyer_name" value="{{$buyer->name}}">
                        <label for="exampleFormControlTextarea1">Tell us about your experience:</label>
                        <textarea class="form-control" id="exampleFormControlTextarea1" rows="5" name="description"></textarea>
                        <label for="exampleFormControlTextarea1">*Rate the user:</label>
                        <input type="radio" value="1" name="rating" required/>1
                        <input type="radio" value="2" name="rating" />2
                        <input type="radio" value="3" name="rating" />3
                        <input type="radio" value="4" name="rating" />4
                        <input type="radio" value="5" name="rating" />5
                        <input class="btn btn-warning btn-lg btn-block my-3" type="submit" id="review-btn" value="Review">
                    </form>
                </div>
            </div>

       </div>
   </div>


  </div>


  <!-- <p class = "text-center">fdsfdusibf
    sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6
  </p> -->

  <!-- <script src="https://code.jquery.com/jquery-3.4.1.slim.min.js" integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
  <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js" integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6" crossorigin="anonymous"></script>
    -->

@endsection
