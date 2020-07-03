<?php

namespace App\Policies;

use App\User;

use Illuminate\Auth\Access\HandlesAuthorization;

class ProfilePolicy
{
    use HandlesAuthorization;


    public function ban(User $cur_user, User $user)
    {
      return $cur_user->is_admin;
    }
}
