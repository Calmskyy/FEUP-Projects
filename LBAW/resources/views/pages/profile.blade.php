@extends('layouts.app')

@section('pageTitle', $user->name)

@section('cssImports')

<link href="{{ asset('css/profile.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
@endsection

@section('content')

<div class="row">
<div class="col">

<div class="container-1">
    @if (!is_null($user->imageUser))
        <!-- <p> {{ $user->imageUser->image['url'] }} </p> -->
        <img id="avatar" src="{{asset('/images/users/' . $user->imageUser->image['url'])}}" alt="User's avatar"></img>
    @else
        <img id="avatar" src="{{asset('/images/users/default.png')}}" alt="User's avatar"></img>
    @endif
    <!-- <img id="avatar" src="{{asset('/images/users/default.png')}}" alt="User's avatar"></img> -->
    <div id="identification">
      <h1>{{ $user->name }}</h1>
      <h1>Reputation:</h1>
      @for ($i = 0; $i < $user->reputation; $i++)
        <span class="fa fa-star checked"></span>
      @endfor
      @for (; $i < 5; $i++)
        <span class="fa fa-star"></span>
      @endfor
    </div>
    <div id="contacts">
      <i class="fa fa-phone-square"></i>
      <h1>{{ $user->phone_number }}</h1><br>
      <i class="fa fa-envelope-square"></i>
      <h1>{{ $user->email }}</h1>
      @if(!Auth::guest() && $user->id == Auth::user()->id)
        <a class="btn btn-primary" href="{{ route('profile_edit', $user->id) }}"> Edit Profile  </a>
      @endif
    </div>
</div>
  <div class="container-2">
    <div class="info">
      <h2>Biography</h2>
      <p>
        {{ $user->biography }}
      </p>
      <h2>Interests:</h2>
      <ul>
        @foreach($user->interests as $interest)
            <!-- <li>{{$interest->type}}</li> -->
            <li>{{ $interest->type }}</li>
        @endforeach
      </ul>
      <h2>What others say about {{ $user->name }}:</h2>
      @if ($user['banned'])
          <h1>BANNED USER</h1>
      @endif
      @if (!is_null(Auth::user()) && Auth::user()['is_admin'])
          <!-- Button trigger modal -->
          <button type="button" class="btn btn-danger" data-toggle="modal" data-target="#exampleModal">
          Ban User
          </button>

          <!-- Modal -->
          <div class="modal fade" id="exampleModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
              <div class="modal-dialog modal-dialog-centered" role="document">
                  <div class="modal-content">
                      <form method="POST" action="{{ route('ban_user', $user->getId()) }}">
                          {{ csrf_field() }}
                          <div class="modal-header">
                              <h5 class="modal-title" id="exampleModalLabel">Reason for ban user</h5>
                              <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                              <span aria-hidden="true">&times;</span>
                              </button>
                          </div>
                          <div class="modal-body">
                              <textarea name="reason" type="textarea">Reason...</textarea>
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
      @foreach($user->reviewsReceived as $review)
        <div class="review">
            @can('delete', $review)
                <form action="{{ route('review_delete', ['buyer_id'=>$review->buyer_id, 'seller_id'=>$review->seller_id, 'item_id'=>$review->title]) }}" method="POST">
                    <input type="hidden" name="_method" value="DELETE">
                    <input type="hidden" name="_token" value="{{ csrf_token() }}">
                    <input class="btn" type="submit" value="Delete">
                </form>
            @endcan
            @if (!is_null($review->buyer->imageUser))
                <img class="review-avatar" src="{{asset('/images/users/' . $review->buyer->imageUser->image['url'])}}" alt="User's avatar"></img>
            @else
                <img class="review-avatar" src="{{asset('/images/users/default.png')}}" width="50" height="50" alt="User's avatar"></img>
            @endif
            <!-- <img class="review-avatar" src="{{asset('/images/users/default.png')}}"></img> -->
            <h5>{{ $review->buyer['name'] }}</h5>
            <!-- <h5>{{ $review->buyer->imageUser->image['url'] }}</h5> -->
            @for ($i = 0; $i < $review->rating; $i++)
                <span class="fa fa-star checked"></span>
            @endfor
            @for (; $i < 5; $i++)
                <span class="fa fa-star"></span>
            @endfor
            <p>
            {{ $review->description }}
            </p>
        </div>
      @endforeach

      @if(!Auth::guest() && $user->id == Auth::user()->id)
        <h2></br>Purchase history</h2>
        <div class="row">
        @foreach($user->itemsPurchased as $history_element)
        <div class="colummn">
          <div class="panel panel-default" id="history_element">
            <div class="panel-body">
              <p>Item: {{$history_element->title}}</p>
              <p>Price: {{$history_element->price}} EUR</p>
              <p>Seller: {{$history_element->seller->name}}</p>
            </div>
          </div>    
          @if(!$history_element['reviewed'])
          <div class="panel panel-default" id="history_element">
            <div class="panel-heading">
              <div class="form-group">
                  <a href="{{ route('review', ['buyer_id'=>Auth::user()->id, 'seller_id'=>$history_element->seller->id, 'title'=>$history_element->title])}}" class="review-btn">Review seller</a>
              </div>
            </div>
          </div>
          @endif
        </div>
        @endforeach
        </div>
      @endif
      <!-- <div class="review">
        <img class="review-avatar" src="{{asset('/images/users/default.png')}}"></img>
        <span class="fa fa-star checked"></span>
        <span class="fa fa-star checked"></span>
        <span class="fa fa-star checked"></span>
        <span class="fa fa-star checked"></span>
        <span class="fa fa-star"></span>
        <p>
          Lorem ipsum dolor sit amet consectetur adipisicing elit.
          Officiis necessitatibus minus qui excepturi obcaecati tenetur,
          dicta inventore! Vel necessitatibus consectetur cumque tempora
          eaque nulla totam rem provident, a ducimus consequatur.
        </p>
      </div>
      <div class="review">
        <img class="review-avatar" src="{{asset('/images/users/default.png')}}"></img>
        <span class="fa fa-star checked"></span>
        <span class="fa fa-star checked"></span>
        <span class="fa fa-star checked"></span>
        <span class="fa fa-star checked"></span>
        <span class="fa fa-star"></span>
        <p>
          Aenean accumsan erat quam, ut volutpat risus fringilla interdum. 
          Phasellus vel sapien fermentum tellus aliquet viverra. Integer ac eros leo. 
          Cras eget purus interdum libero fermentum volutpat in ac diam. 
          Cras quis condimentum tortor, sit amet mollis orci. Aenean vitae arcu porttitor, pharetra est ut, euismod massa. 
          Sed eleifend fermentum cursus. Cras sed ex rhoncus, euismod lorem a, facilisis risus. 
          Donec sollicitudin semper diam vitae vulputate. 
        </p>
      </div> -->
    </div>
  </div>

</div>
</div>

@endsection