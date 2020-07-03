<?php

namespace App\Http\Controllers;

use App\User;
use App\Interest;

use App\Action;
use App\BanUser;

use App\Image;
use App\ImageUser;

use Illuminate\Http\Request;

// use Illuminate\Support\Facades\DB;
use Illuminate\Support\Facades\Auth;

class ProfileController extends Controller
{

    public function show($id)
    {
      $user = User::find($id);
      // $interests = $user->interests();

      // $this->authorize('show', $user);

      return view('pages.profile', ['user' => $user]);
    }

    public function ban(Request $request, $id){

      $user = User::find($id);

      $this->authorize('ban', $user);

      $action = Action::create(['reason' => $request->reason ,
                                'moderator_id' => Auth::user()->getId(),
                                'date' => date("Y-m-d")]);

      $stop_sale = BanUser::create(['action_id' => $action['id'],
                                      'user_id' => $user->getId()]);

      return redirect()->route('profile', $id);
    }

    public function edit($id)
    {
      $user = Auth::user();

      return view('pages.profile_edit', ['user' => $user]);
    }

    public function update(Request $request, $id)
    {
      $user = Auth::user();

      // UPDATE NAME PHONE EMAIL AND BIOGRAPHY

      $user->update(['name' => $request->name ,
                      'phone_number'  => $request->phone_number,
                      'email' => $request->email,
                      'biography' => $request->biography]);

      // UPDATE PROFILE IMAGE

      if($file = $request->file('avatar')) {

        $imageUser = $user->imageUser();

        if($user->imageUser != null){

          $image = $user->imageUser->image();

          if($image != null){

            $imageUser->delete();

            $image->delete();
          }
        }

        $extension = $request->avatar->getClientOriginalExtension();  //Get Image Extension
        $name=$file->getClientOriginalName();
        $fileName = $name;  //Concatenate both to get FileName (eg: file.jpg)
        $destinationPath = public_path('/images/users');
        //dd($fileName);
        $file->move($destinationPath, $fileName);  

        $imageObj = Image::create(['url' => $fileName]);

        $imageUserObj = ImageUser::create(['image_id' => $imageObj['id'],
                                                'user_id' => $user['id']]);
      }


      if ($request->Painting){
        if (!$user->hasInterest('Painting')){
          Interest::create(['user_id' => $user->getId(),
                            'type' => 'Painting']);
        }
      } else {
        if ($user->hasInterest('Painting')){
          Interest::where('user_id', '=', $user->getId())
                ->where('type', '=', 'Painting')
                ->first()->delete();
        }
      }

      if ($request->Sculpture){
        if (!$user->hasInterest('Sculpture')){
          Interest::create(['user_id' => $user->getId(),
                            'type' => 'Sculpture']);
        }
      } else {
        if ($user->hasInterest('Sculpture')){
          Interest::where('user_id', '=', $user->getId())
                ->where('type', '=', 'Sculpture')
                ->first()->delete();
        }
      }

      if ($request->Photography){
        if (!$user->hasInterest('Photography')){
          Interest::create(['user_id' => $user->getId(),
                            'type' => 'Photography']);
        }
      } else {
        if ($user->hasInterest('Photography')){
          Interest::where('user_id', '=', $user->getId())
                ->where('type', '=', 'Photography')
                ->first()->delete();
        }
      }

      if ($request->Drawing){
        if (!$user->hasInterest('Drawing')){
          Interest::create(['user_id' => $user->getId(),
                            'type' => 'Drawing']);
        }
      } else {
        if ($user->hasInterest('Drawing')){
          Interest::where('user_id', '=', $user->getId())
                ->where('type', '=', 'Drawing')
                ->first()->delete();
        }
      }

      if ($request->Serigraphy){
        if (!$user->hasInterest('Serigraphy')){
          Interest::create(['user_id' => $user->getId(),
                            'type' => 'Serigraphy']);
        }
      } else {
        if ($user->hasInterest('Serigraphy')){
          Interest::where('user_id', '=', $user->getId())
                ->where('type', '=', 'Serigraphy')
                ->first()->delete();
        }
      }

      if ($request->Ceramics){
        if (!$user->hasInterest('Ceramics')){
          Interest::create(['user_id' => $user->getId(),
                            'type' => 'Ceramics']);
        }
      } else {
        if ($user->hasInterest('Ceramics')){
          Interest::where('user_id', '=', $user->getId())
                ->where('type', '=', 'Ceramics')
                ->first()->delete();
        }
      }

      //$interests = Interest::where('user_id', '=', $user->id)->get();
      /*
      $int = $request->input('Serigraphy');
      $isInterest = false;
      if ($int == true) {
        $interest = Interest::where('user_id', '=', $user->getId())->get();
        foreach ($interest as $interest){
          if ($interest->type == $int){
            $isInterest = true;
            break;
          }
        }
        if(!$isInterest) {
          $interestObj = Interest::create(['user_id' => $user->getId(), 'type' => 'Serigraphy']);
        }
      }
      elseif ($int == null){
        $interest = Interest::where('user_id', '=', $user->getId())->get();
        foreach ($interest as $interest){
          if ($interest->type == $int){
            $interest.delete();
          }
        }
      }*/

      return redirect()->route('profile', $id);
    }

}
