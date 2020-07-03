<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class NotificationItem extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'notification_item';

  protected $primaryKey = 'notification_id';

  public function notification(){
    return $this->belongsTo('App\Notification', 'notification_id');
  }

  public function item(){
    return $this->belongsTo('App\Item');
  }

}	