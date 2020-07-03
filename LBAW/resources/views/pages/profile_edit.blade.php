@extends('layouts.app')

@section('pageTitle', $user->name . ' - Edit')

@section('cssImports')

<link href="{{ asset('css/profile_edit.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
@endsection

@section('content')

<div class="prof-edit-container">
    <div class="d-flex justify-content-center h-100">
    <div class="card">

    <!-- PICTURE CARD -->
      <h1>Edit Profile</h1>
        <form  method = "POST" enctype="multipart/form-data" action = "{{ route('profile_edit', $user->id) }}">
        {{ csrf_field() }}
          <div class="edit-form">
          @if (!is_null($user->imageUser))
            <img id="avatar" src="{{asset('/images/users/' . $user->imageUser->image['url'])}}" alt="User's avatar"></img>
          @else
            <img id="avatar" src="{{asset('/images/users/default.png')}}" alt="User's avatar"></img>
          @endif
          </div>
            <input type="file" name="avatar">
          <div class="edit-form">
            <h2>*new username:</h2>
            <input name="name" type="text" value="{{ $user->name }}" required>
          </div>

          <div class="edit-form">
            <h2>*new phone number:</h2>
            <input name="phone_number" type="text" value="{{ $user->phone_number }}" required>
          </div>
        
          <div class="edit-form">
            <h2>*new email:</h2>
            <input name="email" type="text" value="{{ $user->email }}" required>
          </div>

      <!-- BIOGRAPHY CARD -->
      
          <div class="edit-form">
          <h2>about me:</h2>
            <textarea name="biography" rows="4" cols="40">
               {{ $user->biography }}
            </textarea>
          </div>

      <!-- INTERESTS CARD -->
        <h2>my interests:</h2>
          <ul>
            <li>
              @if( $user->hasInterest('Painting') )
                  <input type="checkbox" name="Painting" value="true" checked="checked">Painting
              @else
                  <input type="checkbox" name="Painting" value="false">Painting
              @endif
            </li>
            <li>
              @if( $user->hasInterest('Sculpture') )
                  <input type="checkbox" name="Sculpture" value="Sculpture" checked="checked">Sculpture
              @else
                  <input type="checkbox" name="Sculpture" value="Sculpture">Sculpture
              @endif
            </li>
            <li>
              @if( $user->hasInterest('Photography') )
                  <input type="checkbox" name="Photography" value="Photography" checked="checked">Photography
              @else
                  <input type="checkbox" name="Photography" value="Photography">Photography
              @endif
            </li>
            <li>
              @if( $user->hasInterest('Drawing') )
                  <input type="checkbox" name="Drawing" value="Drawing" checked="checked">Drawing
              @else
                  <input type="checkbox" name="Drawing" value="Drawing">Drawing
              @endif
            </li>
            <li>
              @if( $user->hasInterest('Serigraphy') )
                  <input type="checkbox" name="Serigraphy" value="true" checked="checked">Serigraphy
              @else
                  <input type="checkbox" name="Serigraphy" value="false">Serigraphy
              @endif
            </li>
            <li>
              @if( $user->hasInterest('Ceramics') )
                  <input type="checkbox" name="Ceramics" value="Ceramics" checked="checked">Ceramics
              @else
                  <input type="checkbox" name="Ceramics" value="Ceramics">Ceramics
              @endif
              </li>
          </ul>
          <div class="edit-form">
            <input type="submit" class="btnSubmit" value="Submit" />
            @if ($errors->any())
              <div class="alert alert-danger">
                  <ul>
                      @foreach ($errors->all() as $error)
                          <li>{{ $error }}</li>
                      @endforeach
                  </ul>
              </div>
            @endif
          </div>
        </form>
      </div>
    </div>
</div>


@endsection