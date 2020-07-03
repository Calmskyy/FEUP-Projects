<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

use Illuminate\Support\Facades\Input;
use App\Item;
use App\ItemAuction;
use App\ItemPurchase;

Route::get('/', 'HomeController@show');

// Authentication

Route::get('login', 'Auth\LoginController@showLoginForm')->name('login');
Route::post('login', 'Auth\LoginController@login');
Route::get('logout', 'Auth\LoginController@logout')->name('logout');
Route::get('register', 'Auth\RegisterController@showRegistrationForm')->name('register');
Route::post('register', 'Auth\RegisterController@register');

// Route::get('search', 'SearchController@show')->name('search');


Route::get('item/{id}', 'ItemController@show')->name('item');
Route::get('item', 'ItemController@create_view')->name('item_create');
Route::post('item', 'ItemController@create')->name('item_create');
Route::get('item/{id}/edit', 'ItemController@edit')->name('item_edit');
Route::post('item/{id}/edit', 'ItemController@update')->name('item_edit');
Route::post('item/{id}/stop', 'ItemController@stop')->name('item_stop');
Route::delete('item/{id}/delete', 'ItemController@destroy')->name('item_remove');

Route::post('comment/{id}/mod_delete', 'CommentController@mod_delete')->name('comment_mod_delete');
Route::post('comment/{id}/delete', 'CommentController@delete')->name('comment_delete');
Route::post('comment/{id}/edit', 'CommentController@edit')->name('comment_edit');
Route::post('createComment', 'CommentController@insertComment')->name('comment_insert');

Route::get('profile/{id}', 'ProfileController@show')->name('profile');
Route::post('profile/{id}/ban', 'ProfileController@ban')->name('ban_user');
Route::get('profile/{id}/edit', 'ProfileController@edit')->name('profile_edit');
Route::post('profile/{id}/edit', 'ProfileController@update')->name('profile_edit');

//Reviews
Route::get('review/{buyer_id}/{seller_id}/{title}', 'ReviewController@show')->name('review');
Route::post('create', 'ReviewController@insertReview');
Route::delete('profile/{buyer_id}/{seller_id}/{item_id}', 'ReviewController@destroy')->name('review_delete');

// Static Pages
Route::get('about', 'AboutController@show')->name('about');
Route::get('faq', 'FAQController@show')->name('faq');
Route::get('contacts', 'ContactsController@show')->name('contacts');

//Homepage
Route::get('home', 'HomeController@show')->name('home');

// Search

Route::get('search', 'SearchController@search')->name('search');

//PayPal
Route::post('deposit', 'PaymentController@payWithpaypal')->name('deposit');
Route::post('withdrawal', 'PaymentController@paidWithpaypal')->name('withdrawal');
Route::get('deposit/{id}/{amount}', 'PaymentController@getDepositStatus')->name('deposit_status');
Route::get('withdrawal/{id}/{amount}', 'PaymentController@getWithdrawalStatus')->name('withdrawal_status');

//System bank account
Route::get('bankaccount', 'BankAccountController@show')->name('bankaccount');
Route::post('endauction', 'ItemController@finishAuction')->name('endauction');
Route::post('itempurchase', 'ItemController@purchaseItem')->name('itempurchase');
Route::post('bid', 'ItemController@bid')->name('bid');

