<?php

namespace App\Http\Controllers;

use App\Item;
use App\ItemAuction;
use App\ItemPurchase;
use App\Comment;

use App\Image;
use App\ImageItem;

use App\Action;
use App\StopSale;
use App\Bid;
use App\User;
use App\ItemHistory;

use Illuminate\Http\Request;

// use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Auth;

class ItemController extends Controller
{

    public function show($id)
    {
      $item = Item::find($id);
      $itemAuction = ItemAuction::where('item_id', $id)->first();
      $itemPurchase = ItemPurchase::where('item_id', $id)->first();
      $comments = Comment::where('item_id', $id)->get();

      // $this->authorize('show', $item);

      return view('pages.item', ['item' => $item, 'itemAuction' => $itemAuction, 'itemPurchase' => $itemPurchase, 'comments' => $comments]);
    }

    public function create_view(){
      return view('pages.item_sell', []);
    }

    public function create(Request $request){

      $this->validate($request, [
        'images' => 'required|min:1|max:5',
        'images.*' => 'image|mimes:jpeg,png,jpg,gif,svg'
      ]);

      $item = Item::create(['title' => $request->title ,
                            'description' => $request->description,
                            'type' => $request->category,
                            'seller_id' => Auth::user()->getId(),
                            'start_time' => date("Y-m-d"),
                            'stopped' => false
                            ]);

      if ($request['sell-type'] == 'Sale'){
        $itemPurchase = ItemPurchase::create(['item_id' => $item['id'],
                                              'price' => $request->price]);
      } else if ($request['sell-type'] == 'Auction'){

        $itemAuction = ItemAuction::create(['item_id' => $item['id'],
                                            'starting_bid' => $request->price,
                                            'bid_difference' => $request->difference,
                                            'end_time' => strtotime($request['limit_date'] . " " . $request['limit_hour'])]);
      }

      

      if($files=$request->file('images')){
        foreach($files as $file){
            $milliseconds = round(microtime(true) * 1000);
            $name = $milliseconds.'.'.$file->getClientOriginalExtension();
            $destinationPath = public_path('/images/items');
            // $name=$file->getClientOriginalName();
            $file->move($destinationPath, $name);
            $images[]=$name;

            $imageObj = Image::create(['url' => $name]);

            $imageItemObj = ImageItem::create(['image_id' => $imageObj['id'], 
                                                'item_id' => $item['id']]);
        }
      }      

      return redirect()->route('item', $item['id']);
    }
    
    public function edit($id)
    {
      $item = Item::find($id);
      $itemAuction = ItemAuction::where('item_id', $id)->first();
      $itemPurchase = ItemPurchase::where('item_id', $id)->first();

      $this->authorize('update', $item);

      return view('pages.item_edit', ['item' => $item, 'itemAuction' => $itemAuction, 'itemPurchase' => $itemPurchase]);
    }

    public function update(Request $request, $id)
    {
      $item = Item::find($id);

      $this->authorize('update', $item);

      $item->update(['title' => $request->title ,
                      'description' => $request->description]);

      if($files=$request->file('images')){

        $imagesItemToDelete = $item->imagesItem()->get();

        foreach( $imagesItemToDelete as $imageItem){
          $image = $imageItem->image();

          $imageItem->delete();

          $image->delete();
        }

        foreach($files as $file){
            $milliseconds = round(microtime(true) * 1000);
            $name = $milliseconds.'.'.$file->getClientOriginalExtension();
            $destinationPath = public_path('/images/items');
            // $name=$file->getClientOriginalName();
            $file->move($destinationPath, $name);
            $images[]=$name;

            $imageObj = Image::create(['url' => $name]);

            $imageItemObj = ImageItem::create(['image_id' => $imageObj['id'], 
                                                'item_id' => $item['id']]);
        }
      }

      return redirect()->route('item', $id);
    }

    public function stop(Request $request, $id)
    {
      $item = Item::find($id);

      $this->authorize('stop', $item);

      $action = Action::create(['reason' => $request->reason ,
                                'moderator_id' => Auth::user()->getId(),
                                'date' => date("Y-m-d")]);

      $stop_sale = StopSale::create(['action_id' => $action['id'],
                                      'item_id' => $item['id']]);

      return redirect()->route('item', $id);
    }

    public function destroy($id){
      //need to make trigger
      Item::where('id', $id)->delete();      

      return redirect()->route('home');
    }
    
    public function finishAuction(Request $request){

      $seller_id = $request->input('seller_id');
      $item_id = $request->input('item_id');
      $amount = $request->input('last_bid');

      $last_bid = Bid::where('item_id', $item_id)->first();
      if(is_null($last_bid)){
        Item::where('id', $item_id)->delete();
        return redirect()->route('profile', $seller_id);
      }
      
      $buyer_id = Bid::where([
                    ['item_id', '=', $item_id],
                    ['bid_amount', '=', $amount
                    ]])->value('bidder_id');
                    
      $title = Item::where('id', $item_id)->value('title');

      //conta do seller recebe dinheiro
      $old_amount_seller = User::where('id', $seller_id)->value('cash');
      $amount_seller = $amount + $old_amount_seller;
      User::where('id', $seller_id)->update(['cash'=>$amount_seller]);

      //conta do buyer perde dinheiro
      $old_amount_buyer = User::where('id', $buyer_id)->value('cash');
      $amount_buyer = $old_amount_buyer - $amount;
      User::where('id', $buyer_id)->update(['cash'=>$amount_buyer]);

      //adicionar ao historico de compras do buyer
      $data = array('buyer_id'=>$buyer_id, 'seller_id'=>$seller_id, 'title'=>$title, 'price'=>$amount, 'reviewed'=>'false');
      ItemHistory::insert($data);

      //eliminar item da base de dados
      Item::where('id', $item_id)->delete();

      return redirect()->route('profile', $buyer_id);


    }

    public function purchaseItem(Request $request){
      $seller_id = $request->input('seller_id');
      $item_id = $request->input('item_id');
      $amount = $request->input('price');
      $buyer_id = $request->input('buyer_id');

      $title = Item::where('id', $item_id)->value('title');

      //conta do seller recebe dinheiro
      $old_amount_seller = User::where('id', $seller_id)->value('cash');
      $amount_seller = $amount + $old_amount_seller;
      User::where('id', $seller_id)->update(['cash'=>$amount_seller]);

      //conta do buyer perde dinheiro
      $old_amount_buyer = User::where('id', $buyer_id)->value('cash');
      $amount_buyer = $old_amount_buyer - $amount;
      User::where('id', $buyer_id)->update(['cash'=>$amount_buyer]);

      //adicionar ao historico de compras do buyer
      $data = array('buyer_id'=>$buyer_id, 'seller_id'=>$seller_id, 'title'=>$title, 'price'=>$amount, 'reviewed'=>'false');
      ItemHistory::insert($data);

      //eliminar item da base de dados
      Item::where('id', $item_id)->delete();

      return redirect()->route('profile', $buyer_id);


    }

    public function bid(Request $request){

      $bidder_id = $request->input('bidder_id');
      $item_id = $request->input('item_id');
      $amount_inserted = $request->input('amount');

      date_default_timezone_set('Europe/Lisbon');
      $date = date('m/d/Y h:i:s a', time());

      $last_amount = Bid::where('bidder_id', $request->input('bidder_id'))->value('bid_amount');

      if(!is_null($last_amount)){
        Bid::where('bidder_id', $request->input('bidder_id'))->delete();
      }

      //delaying auction end
      $end_date = ItemAuction::where('item_id', $item_id)->value('end_time');
      $current_date = date("Y-m-d H:i:s");

      $timestampend = strtotime($end_date);
      $timestampcurr = strtotime($current_date);

      $difference = $timestampend - $timestampcurr;

      $hours = date('H', $difference);
      $minutes = date('i', $difference);

      if($hours < 2){
          if($minutes < 10){
                  $new_time = $timestampend + 600;
                  ItemAuction::where('item_id', $item_id)->update(['end_time' => date("Y-m-d H:i:s", $new_time)]);
          }
      }            
      
      //inserting bid on table
      $data = array('bidder_id'=>$bidder_id, "item_id"=>$item_id, "bid_amount"=>$amount_inserted, "date"=>$date);
      Bid::insert($data);

      //updating current bid
      ItemAuction::where('item_id', $request->input('item_id'))->update(['current_bid' => $request->input('amount')]);

      return redirect()->route('item', $item_id);
    }

}
