# Remote Server
Server to acces the Wombat's motors / servos / etc.

<br><br>

# Protocol
The base request must contain the key `type`, which can either have the value `get` or `post`:
```json
{
  "type": "get|post",
  ...
}
```

## get
When requesting a `get`, the message must contain the `request` key, which
can have following values:

* `motor` <br>
additionally required:
  * `port`: **int**

  returns
  * **int** (-1500...1500) - motor speed

<br>

* `servo` <br>
additionally required:
  * `port`: **int**

  returns
  * **int** (0...2047) - servo position

<br>

* `digital` <br>
additionally required:
  * `port`: **int**

  returns
  * `bool` - value

<br>

* `analog` <br>
additionally required:
  * `port`: **int**

  returns
  * `int` (0...4086) - value

<br>

### Example:
request:
```json
{
  "type": "get",
  "request": "analog",
  "port": 0
}
```

return:
```json
{
  "success": true,
  "value": 1834
}
```
