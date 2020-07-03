@extends('layouts.app')

@section('pageTitle', 'Log in')

@section('content')
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Sign In</title>
  <link rel="stylesheet" href="{{ asset('css/loginpage.css') }}">
</head>

<body>
  <div class="container-fluid">
  </div>
  <div class="login-container">
    <div class="d-flex justify-content-center h-100">
      <div class="card">
        <h1>Sign in to artBay</h1>
        <form  method = "POST" action = "{{ route('login') }}">
        {{ csrf_field() }}
          <div class="form-group">
            <label for="email">*Email Address</label>
            <input type="email" name="email" class="form-control" required autofocus />
          </div>
          <div class="form-group">
            <h2>*Password</h2>
            <input type="password" name='password' class="form-control" placeholder="********" value="" required/>
          </div>
          <div class="form-group">
            <input type="submit" class="btnSubmit" value="Login" />
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
          <div class="form-group">
            <a href="{{ route('register') }}" class="signup">Don't have an account? Sign up</a>
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