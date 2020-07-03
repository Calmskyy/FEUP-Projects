@extends('layouts.app')

@section('pageTitle', 'About artBay')

@section('cssImports')
<link href="{{ asset('css/aboutpage.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
<script src="https://code.jquery.com/jquery-3.4.1.slim.min.js" integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js" integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6" crossorigin="anonymous"></script>
@endsection

@section('content')

<div class="row">
    <div class="col my-4 mx-4">
        <h1 class="text-left" id="about_header">About</h1>
        <p id="p1">Welcome to artBay, the website where you can buy and sell your favorite pieces of art from the comfort of your home! Frequently, we will have the desire to see and/or own a piece of art, only to find out it is in display somewhere far from where we live. It is not always easy for one to go all the way to a gallery or museum in a foreign country, let alone bring a piece of art with them. However, many of these famous items are actually available for public purchase. That's where we - artBay - come in! Through an easy and simple auction system, galleries, museums and private collectors can make their items available for anyone to purchase and bid on. As usual, the highest bidder will take the prize home. You will then be able to enjoy art, while sitting comfortably at home.</p>
        <p id="p2">This website was created by four computer engineering students for the subject of Laboratory of Databases and Web Applications. Our team has always been fond of art in all its shapes and forms, which led us here. We hope you enjoy your stay and engage in the awesome auctions and deals we bring you.
</p>        
    </div>

    <div class="col-12 col-md-3 sidenav flexbox">
        <div id="side-links">
            <form action="{{ route('contacts') }}">
                <input class="btn side-button" type="submit" value="Go to Contacts">
            </form>
            <form action="{{ route('faq') }}">
                <input class="btn side-button" type="submit" value="Go to FAQs">
            </form>
        </div>
    </div>
</div>

@endsection
