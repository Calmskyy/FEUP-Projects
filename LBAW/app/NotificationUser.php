<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class NotificationUser extends Model
{
  // Don't add create and update timestamps in database.
  public $timestamps  = false;
  // Name of sql table
  protected $table = 'notification_user';

  protected $primaryKey = 'notification_id';

  public function notification(){
    return $this->belongsTo('App\Notification', 'notification_id');
  }

  public function user(){
    return $this->belongsTo('App\User');
  }
	
}
