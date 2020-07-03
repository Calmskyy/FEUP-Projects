<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\Input;
use Illuminate\Support\Facades\URL;
use Redirect;
use Session;
use DateTime;

use PayPal\Rest\ApiContext;
use PayPal\Auth\OAuthTokenCredential;
use PayPal\Api\Payer;
use PayPal\Api\ItemList;
use PayPal\Api\Amount;
use PayPal\Api\Transaction;
use PayPal\Api\RedirectUrls;
use PayPal\Api\Payment;
use PayPal\Exception\PayPalConnectionException;
use PayPal\Api\PaymentExecution;
use PayPal\Api\Payee;

use App\Item;
use App\ItemAuction;
use App\ItemPurchase;
use App\Bid;

use App\User;

class PaymentController extends Controller
{
    public function __construct()
    {/** PayPal api context **/
        $paypal_conf = \Config::get('paypal');
        $this->_api_context = new ApiContext(new OAuthTokenCredential(
            $paypal_conf['client_id'],
            $paypal_conf['secret'])
        );
        $this->_api_context->setConfig($paypal_conf['settings']);
    }

    public function payWithpaypal(Request $request)
    {

        $user_id = $request->input('user');
        $amount_inserted = $request->input('amount');

        $payer = new Payer();
        $payer->setPaymentMethod('paypal');
    
        $amount = new Amount();
        $amount->setCurrency('EUR')
                ->setTotal($amount_inserted);     
        
        $transaction = new Transaction();
        $transaction->setAmount($amount)
                ->setDescription('ARTBAY-DEPOSIT');     

        $redirect_urls = new RedirectUrls();
        $redirect_urls->setReturnUrl(URL::route('deposit_status', ['id'=>$user_id, 'amount'=>$amount_inserted]))
                    ->setCancelUrl(URL::route('deposit_status', ['id'=>$user_id, 'amount'=>$amount_inserted]));

        
        $payment = new Payment();
        $payment->setIntent('sale')
                ->setPayer($payer)
                ->setRedirectUrls($redirect_urls)
                ->setTransactions(array($transaction));
        
        try{
            $payment->create($this->_api_context);
        }
        catch(\PayPal\Exception\PayPalConnectionException $ex){
            if(\Config::get('app.debug')){
                \Session::put('error', 'Connection timeout');
                // \Session::put('error', $ex->getMessage());
            }
            else{
                \Session::put('error', 'An error occurred, sorry for the inconveniance.');
            }

            return \Redirect::route('profile', $user_id);
        }

        foreach($payment->getLinks() as $link){
            if($link->getRel() == 'approval_url'){
                $redirect_url = $link->getHref();
                break;
            }
        }

        Session::put('paypal_payment_id', $payment->getId());

        if (isset($redirect_url)) {

            return \Redirect::away($redirect_url);
        }

        \Session::put('error', 'Unknown error occurred');
        return \Redirect::route('profile', $user_id);
    }

    public function paidWithpaypal(Request $request){

        $user_id = $request->input('user');
        $amount_inserted = $request->input('amount');
        $user_email = User::where('id', $user_id)->value('email');

        $amount = new Amount();
        $amount->setCurrency('EUR')
                ->setTotal($amount_inserted);

        $transaction = new Transaction();
        $transaction->setAmount($amount)
                ->setDescription('ARTBAY-WITHDRAWAL');

        $redirect_urls = new RedirectUrls();
        $redirect_urls->setReturnUrl(URL::route('withdrawal_status', ['id'=>$user_id, 'amount'=>$amount_inserted]))
                    ->setCancelUrl(URL::route('withdrawal_status', ['id'=>$user_id, 'amount'=>$amount_inserted]));

        //$payee = new Payee();
        //$payee->setEmail($user_email);

        $payer = new Payer();
        $payer->setPaymentMethod('paypal');


        $payment = new Payment();
        $payment->setIntent('sale')
                ->setPayer($payer)
                //->setPayee($payee)
                ->setRedirectUrls($redirect_urls)
                ->setTransactions(array($transaction));

        
        try{
            $payment->create($this->_api_context);
        }
        catch(\PayPal\Exception\PayPalConnectionException $ex){
            if(\Config::get('app.debug')){
                \Session::put('error', 'Connection timeout');
            }
            else{
                \Session::put('error', 'An error occurred, sorry for the inconveniance.');
            }

            return \Redirect::route('profile', $user_id);
        }

        foreach($payment->getLinks() as $link){
            if($link->getRel() == 'approval_url'){
                $redirect_url = $link->getHref();
                break;
            }
        }

        Session::put('paypal_payment_id', $payment->getId());

        if (isset($redirect_url)) {

            return \Redirect::away($redirect_url);
        }

        \Session::put('error', 'Unknown error occurred');
        return \Redirect::route('profile', $user_id);
        

    }

    public function getDepositStatus($id, $amount)
    {
        

        /**Get the payment ID before the session is clear */
        $payment_id = Session::get('paypal_payment_id');

        /**Clear the paypal session ID */
        Session::forget('paypal_payment_id');
        if(empty(Input::get('PayerID')) || empty(Input::get('token'))){
            \Session::put('error', 'Payment failed');
            return \Redirect::route('faq');
        }

        $payment = Payment::get($payment_id, $this->_api_context);
        $execution = new PaymentExecution();
        $execution->setPayerId(Input::get('PayerID'));

        /**Execute the payment */
        
        try{
            $result = $payment->execute($execution, $this->_api_context);
        }
        catch(\PayPal\Exception\PayPalConnectionException $ex){
            if(\Config::get('app.debug')){
                // \Session::put('error', 'Connection timeout');
                \Session::put('error', 'An error occurred, sorry for the inconveniance.');
                // \Session::put('error', $ex->getData());
            }
            else{
                \Session::put('error', 'An error occurred, sorry for the inconveniance.');
            }

            return \Redirect::route('profile', $id);
        }

        if($result->getState() == 'approved'){

            $old_amount = User::where('id', $id)->value('cash');
            $new_amount = $old_amount + $amount;

            User::where('id', $id)->update(['cash'=>$new_amount]);



            \Session::put('success', 'Payment success');
            return \Redirect::route('profile', $id);
        }

        \Session::put('error', 'Payment failed');
        return \Redirect::route('faq');
        
    }

    public function getWithdrawalStatus($id, $amount){
        /**Get the payment ID before the session is clear */
        $payment_id = Session::get('paypal_payment_id');

        /**Clear the paypal session ID */
        Session::forget('paypal_payment_id');
        if(empty(Input::get('PayerID')) || empty(Input::get('token'))){
            \Session::put('error', 'Payment failed');
            return \Redirect::route('faq');
        }

        $payment = Payment::get($payment_id, $this->_api_context);
        $execution = new PaymentExecution();
        $execution->setPayerId(Input::get('PayerID'));

        /**Execute the payment */
        $result = $payment->execute($execution, $this->_api_context);

        if($result->getState() == 'approved'){

            $old_amount = User::where('id', $id)->value('cash');
            $new_amount = $old_amount - $amount;

            User::where('id', $id)->update(['cash'=>$new_amount]);



            \Session::put('success', 'Payment success');
            return \Redirect::route('profile', $id);
        }

        \Session::put('error', 'Pyament failed');
        return \Redirect::route('faq');
    }

}
