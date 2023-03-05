# Remote Server
Server to acces the Wombat's motors / servos / etc.

<br><br>

# Protocol
The base request must contain the key `type`, which can either have the value `get` or `set`:
```json
{
  "type": "get|set",
  ...
}
```

## get
When requesting a `get`, the message must contain the `request` key, which
can have following values:

* `motor` <br>
additionally required:
  * `port`: **int** (0...3)

  returns
  * `success`: **bool**
  * `value`: **int** (-1500...1500)

<br>

* `servo_pos` <br>
additionally required:
  * `port`: **int** (0...3)

  returns
  * `success`: **bool**
  * `value`: **int** (0...2047)

<br>

* `servo_enabled` <br>
additionally required:
  * `port`: **int** (0...3)

  returns
  * `success`: **bool**
  * `value`: **bool**

<br>

* `digital` <br>
additionally required:
  * `port`: **int** (0...9)

  returns
  * `success`: **bool**
  * `value`: **bool**

<br>

* `analog` <br>
additionally required:
  * `port`: **int** (0...4)

  returns
  * `success`: **bool**
  * `value`: **int** (0...4086)

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

<br><br>

## set
When requesting a `set`, the message must contain the `request` key, which
can have following values:

* `motor` <br>
additionally required:
  * `port`: **int** (0...3)
  * `velocity`: **int** (-1500...1500)

  returns
  * `success`: **bool**

<br>

* `servo_pos` <br>
additionally required:
  * `port`: **int** (0...3)
  * `position`: **int** (0...2047)

  returns
  * `success`: **bool**

<br>

* `servo_enabled` <br>
additionally required:
  * `port`: **int** (0...3)
  * `enabled`: **bool**

  returns
  * `success`: **bool**

<br>

### Example:
request:
```json
{
  "type": "set",
  "request": "motor",
  "port": 0,
  "velocity": 1300
}
```

return:
```json
{
  "success": true
}
```
