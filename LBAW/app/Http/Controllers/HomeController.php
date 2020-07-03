<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\ItemAuction;
use App\ItemPurchase;

class HomeController extends Controller
{
    public function show() {
        $itemAuction = ItemAuction::all();
        $itemPurchase = ItemPurchase::all();

        return view('pages.homepage', ['itemAuction' => $itemAuction, 'itemPurchase' => $itemPurchase]);
    }
}
