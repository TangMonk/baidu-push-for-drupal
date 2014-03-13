<?php
require_once('includes/Baidu-Push-SDK-Php/Channel.class.php');

function baidu_push_services_send($data) {
  global $user;

  // init more information to message
  $data['message'] = array(
    'message' => $data['message'],
    'timestamp' => $_SERVER['REQUEST_TIME'],
    'sender' => $user->uid,
  );

  // get baidu user_id
  $receive_user = user_load($data['uid']);
  $data['user_id'] = $receive_user->field_baidu_user_id['und'][0]['value'];
  $device = $receive_user->field_device['und'][0]['value'];
  switch ($device){
    case 'ios':
      return _push_to_ios($data);
      break;
    case 'android':
      return _push_to_android($data);
      break;
  }
}

function _push_to_android($data) {
  $opt[Channel::USER_ID] = $data['user_id'];
  $opt[Channel::DEVICE_TYPE] = 3;
  $opt[Channel::MESSAGE_TYPE] = $data['message_type']; // 1 notification, 0 message

  return _push_message($message = $data['message'], $optional = $opt);
}

function _push_to_ios($data) {
  $msg = $data['message'];
  $opt[Channel::USER_ID] = $data['user_id'];
  $opt[Channel::DEVICE_TYPE] = 4;
  $opt[Channel::DEPLOY_STATUS] = 1;
  $opt[Channel::MESSAGE_TYPE] = $data['message_type']; // 1 notification, 0 message

  return _push_message($msg, $optional = $opt);
}

function _push_message($message = '',  $optional = NULL) {
  $channel = _load_baidu_push_channel();
  $response =  $channel->pushMessage (1, $message, 'msg_key', $optional);

  if(false === $response) {
    return services_error(t('send message to @user_id failed', array('@user_id' =>$optional[Channel::USER_ID])), 406);
  }else {
    return TRUE;
  }
}
/*
 * use Singleton pattern to load baidu channel class
 */
function _load_baidu_push_channel() {
  static $channel;
  if(!isset($channel)) {
    $channel = new Channel ('X2yaNcLliQWSAFGxpHkp6cwU', 'oj2GZs3phEKo8a0TajMenRwCiavoEAEa') ;
  }
  return $channel;
}


