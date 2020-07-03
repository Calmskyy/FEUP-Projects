<?php

namespace App\Policies;

use App\User;
use App\Comment;

use Illuminate\Auth\Access\HandlesAuthorization;

class CommentPolicy
{
    use HandlesAuthorization;

    public function update(User $user, Comment $comment)
    {
      // User can only update comments they've made
      return $user->id == $comment->user_id;
    }

    public function mod_delete(User $user, Comment $comment)
    {
      // User can only delete other comments if they're a moderator
      return $user->is_admin;
    }

}
