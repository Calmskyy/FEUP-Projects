<?php

namespace App;

use Illuminate\Notifications\Notifiable;
use Illuminate\Foundation\Auth\User as Authenticatable;

class User extends Authenticatable
{
    use Notifiable;

    // Don't add create and update timestamps in database.
    public $timestamps  = false;
    // Name of sql table
    protected $table = 'user';

    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'name', 'email', 'password', 'banned', 'is_admin', 'phone_number', 'biography', 'interests', 'image'
    ];

    /**
     * The attributes that should be hidden for arrays.
     *
     * @var array
     */
    protected $hidden = [
        'password',
    ];

    public function getId(){
        return $this->id;
    }

    public function imageUser(){
        return $this->hasOne('App\ImageUser', 'user_id', 'id');
    }

    public function items(){
        return $this->hasMany('App\Item');
    }

    public function interests(){
        return $this->hasMany('App\Interest', 'user_id', 'id');
    }

    public function reviewsMade(){
        return $this->hasMany('App\Review', 'buyer_id', 'id');
    }

    public function reviewsReceived(){
        return $this->hasMany('App\Review', 'seller_id', 'id');
    }

    public function hasInterest($check){
        foreach ($this->interests()->get() as $interest) {
            if ($interest->type == $check){
                return true;
            }
        }
        return false;
    }
    
    public function itemsPurchased(){
        return $this->hasMany('App\ItemHistory', 'buyer_id', 'id');
    }

    public function notifications(){
        return $this->hasMany('App\Notification', 'user_id', 'id');
    }
}
