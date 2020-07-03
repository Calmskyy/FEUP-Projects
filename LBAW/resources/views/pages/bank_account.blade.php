@extends('layouts.app')

@section('pageTitle', 'Bank account')

@section('cssImports')

<link href="{{ asset('css/bank_account.css') }}" rel="stylesheet">

@endsection

@section('jsImports')
@endsection

@section('content')

    <div class="col-12 text-center ">

        <div class="mt-4">
            <h2>Bank account of {{Auth::user()->name}}</h2>
            <br>
            <br>
            <br>
            <br>
            <div class="row">
                <div class="column">
                    <h3>Make a deposit<h3>
                    <p>Make a deposit to your account via PayPal, and start bidding on items! You can also purchase items that are available for direct purchase.<p>
                    <br>
                    <br>
                    <form action="/deposit" method="POST">
                        <input type="hidden" name="_token" value="{{ csrf_token() }}">
                        <input type="hidden" name="user" value="{{ Auth::user()->id }}">
                        <input type="number" name="amount" min="10" id="amount" placeholder="*Enter amount" required><br><br>
                        <input class="btn btn-warning btn-lg btn-block my-3" type="submit" id="review-btn" value="Deposit now!">
                    </form>
                </div>
                <div class="column">
                    <h3>Withdrawal<h3>
                    <p>Fast and easy! Withdraw money from your account on our website to your PayPal wallet.<p><br><br><br>
                    <form action="/withdrawal" method="POST">
                        <input type="hidden" name="_token" value="{{ csrf_token() }}">
                        <input type="hidden" name="user" value="{{ Auth::user()->id }}">
                        <input type="number" name="amount" min="10" max="{{ Auth::user()->cash }}"id="amount" placeholder="*Enter amount" required><br><br>
                        <input class="btn btn-warning btn-lg btn-block my-3" type="submit" id="review-btn" value="Withdraw">
                    </form>
                </div>
            </div>
        </div>

    </div>
    <br>
    <br>
    <br>
    <br>
    <br>
    <br>
    <br>
    <br>





@endsection