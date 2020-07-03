<?php

namespace App\Http\Controllers;

use App\Item;
use App\ItemAuction;
use App\ItemPurchase;

use Illuminate\Http\Request;

class SearchController extends Controller
{
    public function show() {

        $itemAuction = ItemAuction::all();
        $itemPurchase = ItemPurchase::all();

        return view('pages.search', ['itemAuction' => $itemAuction, 'itemPurchase' => $itemPurchase]);
    }

    public function search(Request $request){

        $query = $request->q;
        $category = $request->category;

        if (is_null($category) || $category == ""){
            $items = Item::where('title', 'LIKE','%'.$query.'%')->get();
        } else {
            $items = Item::where([['title', 'LIKE','%'.$query.'%'],
                                    ['type', '=', $category]])->get();
        }
   
        $itemAuction = ItemAuction::all();
        $itemPurchase = ItemPurchase::all();
        
        return view('pages.search', ['itemAuction' => $itemAuction, 'itemPurchase' => $itemPurchase, 'category' => $category])->withDetails($items)->withQuery ( $query );
    }

}
