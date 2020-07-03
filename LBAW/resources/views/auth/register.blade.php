@extends('layouts.app')

@section('pageTitle', 'Register')

@section('content')
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Sign up</title>
  <link rel="stylesheet" href="{{ asset('css/signuppage.css') }}">
</head>

<body>
  <div class="container-fluid">
  </div>
  <div class="signup-container">
    <div class="d-flex justify-content-center h-100">
      <div class="card">
        <h1>Create an account</h1>
        <form method="POST" action="{{ route('register') }}">
          {{ csrf_field() }}
          <div class="form-group">
            <h2>*Username</h2>
            <input id="name" type="text" name="name" class="form-control" placeholder="Your Name" value="" required autofocus/>
            @if ($errors->has('name'))
              <span class="error">
                  {{ $errors->first('name') }}
              </span>
            @endif
          </div>
          <div class="form-group">
            <h2>*Email Address</h2>
            <input id="email" type="text" name="email" class="form-control" placeholder="Your Email" value="" required/>
            @if ($errors->has('email'))
              <span class="error">
                  {{ $errors->first('email') }}
              </span>
            @endif
          </div>
          <div class="form-group">
            <h2>*Password</h2>
            <input id="password" type="password" name="password" class="form-control" placeholder="********" value="" required/>
            @if ($errors->has('password'))
              <span class="error">
                  {{ $errors->first('password') }}
              </span>
            @endif
          </div>
          <div class="form-group">
            <h2>*Confirm Password</h2>
            <input id="password_confirmation" type="password" name="password_confirmation" class="form-control" placeholder="********" value="" required/>
          </div>
          <div class="form-group">
            <input type="submit" class="btnSubmit" value="Sign Up" />
          </div>
          <div class="form-group">
            <a href="{{ route('login') }}" class="login">Already have an account? Sign in</a>
          </div>
        </form>
      </div>
    </div>
  </div>

  <script src="https://code.jquery.com/jquery-3.4.1.slim.min.js"
    integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n"
    crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js"
    integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo"
    crossorigin="anonymous"></script>
  <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js"
    integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6"
    crossorigin="anonymous"></script>
</body>

</html>
@endsection
