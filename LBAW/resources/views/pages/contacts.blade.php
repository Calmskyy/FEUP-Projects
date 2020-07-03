@extends('layouts.app')

@section('pageTitle', 'Contact us')

@section('cssImports')
<link href="{{ asset('css/contactspage.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
<script src="https://code.jquery.com/jquery-3.4.1.slim.min.js" integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js" integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6" crossorigin="anonymous"></script>
<script type="text/javascript" src="{{ URL::asset('js/sendEmail.js') }}" defer></script>
@endsection

@section('content')

<div class="row">
    <div class="col mt-5 text-center">
        <h1 class="text-center">Contact Us</h1>
        <p class="text-center">If you wish to talk to our team, please fill in the following form and we will reply as soon as possible</p>
        <form>
            <div class="form-group">
                <input type="text" class="form-control" placeholder="Username">
            </div>
            <div class="form-group">
                <input type="email" class="form-control" placeholder="Email Address">
            </div>
            <div class="form-group">
                <select class="form-control">
                    <option>Choose a category...</option>
                    <option>Catalog information</option>
                    <option>Payments and refunds</option>
                    <option>Shipping</option>
                    <option>Other</option>
                </select>
            </div>
            <div class="form-group">
                <textarea class="form-control" rows="3" placeholder="Message"></textarea>
            </div>
            <div class="text-center">
                <button class="btn" type="submit">Send</button>
            </div>
        </form>
    </div>
</div>

@endsection

