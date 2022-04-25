# logger

Logger macro utility inspired on GLogs

Serializes the message and the severity level into a std::string.

Usage example
```c++
LOG(logger::WARNING, send) << "Exception ocurred: " << e.what();
```

The user callback will be called at the end of the scope.

Example of user callback
```c++
void send(std::string str)
{
  if (logger::get_severity(str) >= logger::WARNING) {
    push_message_to_a_server_with_priority(logger::get_message(str));
  } else {
    push_message_to_a_server(logger::get_message(str));
  }
}
```

## Future work

* Add options to include line, file, date, etc.
* Add macro to disable it
* Add unitary tests
