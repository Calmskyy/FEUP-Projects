<!DOCTYPE html>
<html lang="{{ app()->getLocale() }}">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <!-- CSRF Token -->
    <meta name="csrf-token" content="{{ csrf_token() }}">

    <!--title>{{ config('app.name', 'Laravel') }}</title-->

    <title>@yield('pageTitle')</title>

    <!-- Styles -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <link href="{{ asset('css/stylesheet.css') }}" rel="stylesheet">

    @section('cssImports')
    @show

    <script type="text/javascript">
        // Fix for Firefox autofocus CSS bug
        // See: http://stackoverflow.com/questions/18943276/html-5-autofocus-messes-up-css-loading/18945951#18945951
    </script>
    <!-- <script type="text/javascript" src={{ asset('js/app.js') }} defer></script> -->

    @section('jsImports')
    @show

  </head>
  <body>
    @if ($message = Session::get('success'))
    <div class="w3-panel w3-green w3-display-container" id="success">
        <span onclick="this.parentElement.style.display='none'"
                class="w3-button w3-green w3-large w3-display-topright">&times;</span>
        <p>{!! $message !!} &#9989</p>
    </div>
    <?php Session::forget('success');?>
    @endif

    @if ($message = Session::get('error'))
    <div class="w3-panel w3-red w3-display-container" id="error">
        <span onclick="this.parentElement.style.display='none'"
                class="w3-button w3-red w3-large w3-display-topright">&times;</span>
        <p>{!! $message !!} &#10060</p>
    </div>
    <?php Session::forget('error');?>
    @endif
    <div class="container-fluid">
      <div class="row">
        <div class="col bg-warning">
            
            
          <div class="navbar-top-links">
              <a href="{{ route('about') }}" class="mx-3 ml-5">About</a>
              <a href="{{ route('faq') }}" class="mx-3">FAQ</a>
              <a href="{{ route('contacts') }}" class="mx-3">Contact us</a>
              <div class="float-right">
                  @if (Auth::guest())
                      <a href="{{ route('login') }}" class="mx-1">Login</a>
                      <span>|</span>
                      <a href="{{ route('register') }}" class="mx-1 mr-4">Sign up</a>
                  @else
                      <a href="{{ route('logout') }}" class="mx-1 mr-4">Logout</a>
                  @endif
              </div>

          </div>
          
      
          <nav class="navbar navbar-expand-lg navbar-light">
          <a class="navbar-brand" href="{{ route('home') }}"><img src="{{asset('/images/artBay_logo.png')}}" alt="artBay" height="35"></a>
              <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
                  <span class="navbar-toggler-icon"></span>
              </button>
              
              <div class="collapse navbar-collapse" id="navbarSupportedContent">
                  <form class="form-inline my-2 my-lg-0 mx-auto" id="search-form" action="{{ route('search') }}" method="get">
                      @isset($query)
                      <input id="search_input" value="{{$query}}" class="flex-fill form-control mr-sm-2" type="search" placeholder="Search" aria-label="Search" name="q">
                      @else
                      <input id="search_input" value="" class="flex-fill form-control mr-sm-2" type="search" placeholder="Search" aria-label="Search" name="q">
                      @endisset
                      @isset($category)
                      <input hidden id="search_category" type="text" name="category" value="{{$category}}">
                      @else
                      <input hidden id="search_category" type="text" name="category" value="">
                      @endisset
                      <button id="search" class="btn my-2 my-sm-0" type="submit">Search</button>
                  </form>

                  @if (!Auth::guest())
                    <a href="{{ route('item_create') }}"><span class="fa fa-usd fa-lg p-2 mr-2"></span></a>
                    <div class="nav-item dropdown">
                      <!-- <a class="nav-link text-light" href="#" id="navbarDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        <i class="fa fa-bell"></i>
                      </a> -->
                      <a class="notification" href="#" id="navbarDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        <span class="fa fa-envelope fa-lg p-2 mr-2"></span>
                        <span class="badge">{{count(Auth::user()->notifications()->get())}}</span> 
                      </a>
                      <ul class="dropdown-menu">
                        <li class="head text-light bg-dark">
                          <div class="row">
                            <div class="col-lg-12 col-sm-12 col-12">
                              <span>Notifications ({{count(Auth::user()->notifications()->get())}})</span>
                              <!-- <a href="" class="float-right text-light">Mark all as read</a> -->
                            </div>
                        </li>
                        @each('partials.notification', Auth::user()->notifications()->get(), 'notification')
                        <!-- <li class="footer bg-dark text-center">
                          <a href="" class="text-light">View All</a>
                        </li> -->
                      </ul>
                    </div>
                    <a href="{{ route('bankaccount') }}"><span class="fa fa-cc-paypal fa-2x p-2 mx-1"></span></a>
                    <p>{{  number_format(Auth::user()->cash,2)  }} EUR</p>
                    <a href="{{ route('profile', Auth::user()->id) }}"><span class="fa fa-user-circle fa-2x p-2 mx-1"></span></a>
                    <span>Hello,<br><spam class="font-weight-bold mr-4">{{ Auth::user()->name }}</spam></span>
                  @endif
              </div>
          </nav>
  
          <div class="navbar-top-links d-flex text-center px-5">
              <a href="/search?q=&category=Painting" class="flex-fill">Painting</a>
              <a href="/search?q=&category=Sculpture" class="flex-fill">Sculpture</a>
              <a href="/search?q=&category=Photography" class="flex-fill">Photography</a>
              <a href="/search?q=&category=Drawing" class="flex-fill">Drawing</a>
              <a href="/search?q=&category=Serigraphy" class="flex-fill">Serigraphy</a>
              <a href="/search?q=&category=Ceramics" class="flex-fill">Ceramics</a>
          </div>

        </div>

      </div>

      <!-- <main>
        <header>  
          @if (Auth::check())
          <a class="button" href="{{ url('/logout') }}"> Logout </a> <span>{{ Auth::user()->name }}</span>
          @endif
        </header> -->
        <section id="content">
          @yield('content')
        </section>
      <!-- </main> -->

      <footer class="row mt-5">
        <div class="col bg-warning">
          <div class="d-flex justify-content-center pt-4">
            <img class="mx-4" width="40" height="40" src="{{asset('/images/facebook.png')}}" alt="facebook link">
            <img class="mx-4" width="40" height="40" src="{{asset('/images/instagram.png')}}" alt="instagram link">
            <img class="mx-4" width="40" height="40" src="{{asset('/images/linkedin.png')}}" alt="linkedin link">
          </div>
          <div class="float-right py-1 pr-3">
            <p>Copyright artbay 2020</p>
          </div>
        </div>
      </footer>

    </div>
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" integrity="sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js" integrity="sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI" crossorigin="anonymous"></script>
  </body>
</html>
