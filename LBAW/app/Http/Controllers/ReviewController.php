<?php

namespace App\Http\Controllers;

use App\Review;
use App\User;
use App\Item;
use App\ItemHistory;
use Illuminate\Http\Request;

class ReviewController extends Controller
{
    public function show($buyer_id, $seller_id, $title) {
        $seller = User::find($seller_id);
        $buyer = User::find($buyer_id);
        return view('pages.review', ['buyer'=>$buyer, 'seller'=>$seller, 'title'=>$title]);
    }
    
    public function destroy($buyer_id, $seller_id, $item_id) {

        ItemHistory::where('buyer_id', $buyer_id)
                ->where('seller_id', $seller_id)
                ->where('title', $item_id)
                ->update(['reviewed'=>'false']);

        Review::where('buyer_id', $buyer_id)
                ->where('seller_id', $seller_id)
                ->where('title', $item_id)
                ->delete();

        return redirect()->route('profile', $seller_id);
    }

    public function insertReview(Request $request) {
        $buyer_id = User::select('id')->where('name', $request->input('buyer_name'))->first()->id;
        $seller_id = User::select('id')->where('name', $request->input('seller_name'))->first()->id;
        $title = $request->input('item_title');
        $rating = $request->input('rating');
        $description = $request->input('description');

        $data = array('buyer_id'=>$buyer_id, "seller_id"=>$seller_id, "title"=>$title, "rating"=>$rating, "description"=>$description);
        Review::insert($data);

        ItemHistory::where('buyer_id', $buyer_id)
                    ->where('seller_id', $seller_id)
                    ->where('title', $title)
                    ->update(['reviewed'=>'true']);

        return redirect()->route('profile', $seller_id);
    }
    
}
