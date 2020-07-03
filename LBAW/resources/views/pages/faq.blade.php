@extends('layouts.app')

@section('pageTitle', 'FAQs')

@section('cssImports')
<link href="{{ asset('css/faqpage.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
<script src="https://code.jquery.com/jquery-3.4.1.slim.min.js" integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js" integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6" crossorigin="anonymous"></script>
@endsection

@section('content')
    
<div class="row">
    <div class="col my-4 mx-4">
        <h1 id="title">FAQs</h1>
        <h4 class="question">Q: How do I find an auction to bid on?</h4>
        <p class="reply">A: There are two different ways a user can participate in an auction. On the homepage, there is a section of items that are up for auction. Just click on the image that looks most appealing to you and you will be redirected to the item's page. You can also search for an item using the search bar at the top center of the website.</p>
        <h4 class="question">Q: How do I submit an item to the website?</h4>
        <p class="reply">A: Clicking on the dollar sign at the top right of the screen will lead to you an item submission form. There, you can submit an item of any item type. It will then be available for everyone to see.</p>
        <h4 class="question">Q: I can't bid or buy any items. Are the items not available?</h4>
        <p class="reply">A: Our system runs a bank account for each user. If you do not have enough money in your account, you won't be able to bid or buy items. You must click on the 'PayPal' icon on the top right of the screen in order to make a deposit. If you have enough balance and the problem persists, please contact our team through the 'Contacts' section.</p>    
        <h4 class="question">Q: I just bid on an item, but my balance remains the same. Did the bid go through?</h4>
        <p class="reply">A: After a user has bid on an item, the item's current bead will change to the new value. However, since there is no guarantee it will be the winning bid, we leave the payment process for when the auction is over. Rest assured, if you win the auction, you will be charged for it.</p>  
        <h4 class="question">Q: How do I know if I won an auction?</h4>
        <p class="reply">A: Once an auction has finished, it will show as "Concluded" on its page. After that, the owner of the item needs to finish the auction, and the item will be assigned to the victor. The owner will receive the money the item was sold for, and the bidder will be charged the same amount. At this point, you will be able to review your seller - this is very important and should be taken into account, since it gives us feedback on how the shipping went and rates the seller, impacting their future sales.</p>  
    </div>
    
    <div class="col-12 col-md-3 sidenav flexbox">
        <div id="side-links">
            <form action="{{ route('contacts') }}">
                <input class="btn side-button" type="submit" value="Go to Contacts">
            </form>
            <form action="{{ route('about') }}">
                <input class="btn side-button" type="submit" value="Go to About">
            </form>
        </div>
    </div>  
</div>

@endsection

