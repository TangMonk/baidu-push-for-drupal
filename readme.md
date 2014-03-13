## Baidu Push for Service Module

### usage

1. replace **API Key** and **Secret Key** 
2. Enable **message** resource 
3. Add **baidu_user_id** to user custom field. (the machinname must be ```field_baidu_user_id```)

using this following command to test:

```
curl -H 'Content-type: application/json' \
     -X POST
     -d '{"uid":200,"message":"asdsa","message_type":1}' 
     -H 'X-CSRF-Token:W3GDY9ek2PLpLu3ssKKBeYQ1Z2CDTZ40CZd40L1Xj28' 
     -b 'SESS15bbe3460ffae581febc8d06d5a6791f=EHQLJ-yrgSLbYD_X4snEkj82UFGBRnHYhYq1YIby01Q'
	 http://locahost/api/message/send 
```


### TODO list

1. When Module installed, Add ```baidu_user_id``` field to user field automatic.
2. provide user interface to configuration
