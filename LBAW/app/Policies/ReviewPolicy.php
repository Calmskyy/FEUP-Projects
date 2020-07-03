<?php

namespace App\Policies;

use App\User;
use App\Item;
use App\Review;

use Illuminate\Auth\Access\HandlesAuthorization;

class ReviewPolicy
{
    use HandlesAuthorization;


    public function delete(User $user, Review $review)
    {
      // User can only delete reviews it has written
      //return $user->id == $review->buyer_id;
      return $user->id == $review->buyer_id;
    }
}
