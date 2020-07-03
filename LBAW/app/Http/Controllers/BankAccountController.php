<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class BankAccountController extends Controller
{
    public function show() {
        return view('pages.bank_account');
    }
}