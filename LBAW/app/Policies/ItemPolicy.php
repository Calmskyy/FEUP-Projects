<?php

namespace App\Policies;

use App\User;
use App\Card;
use App\Item;
use App\Bid;

use Illuminate\Auth\Access\HandlesAuthorization;

class ItemPolicy
{
    use HandlesAuthorization;

    public function create(User $user, Item $item)
    {
      // User can only create items in cards they own
      return true;
    }

    public function update(User $user, Item $item)
    {
      // User can only update items in cards they own
      return $user->id == $item->seller_id;
    }

    public function stop(User $user, Item $item)
    {
      // User can only update items in cards they own
      return $user->is_admin;
    }

    public function delete(User $user, Item $item)
    {
        $bid = Bid::where('item_id', $item->id)->first();

      if(!is_null($bid)){
        return false;
      }
      // User can only delete items in cards they own
      return $user->id == $item->seller_id;
    }
    
    public function pay(User $user, Item $item){

      // Users can only purchase or bid on items that are not theirs
      return $user->id != $item->seller_id;
    }
}
