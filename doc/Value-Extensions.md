# Value Extensions

*Warning: The documentation is still work-in-progress and very incomplete.*

--

Value extensions produce a [JAXN] value and can be used wherever a value is expected.
Note that whitespace is significant within value extensions, i.e. whitespace must be used as shown and comments are forbidden.

 * [binary](#binary)
 * [cbor](#cbor)
 * [copy](#copy)
 * [debug](#debug)
 * [env](#env)
 * [jaxn](#jaxn)
 * [json](#json)
 * [msgpack](#msgpack)
 * [parse](#parse)
 * [read](#read)
 * [shell](#shell)
 * [split](#split)
 * [string](#string)
 * [ubjson](#ubjson)

## binary

The `binary` value extension transforms a string value into a binary value.

#### Example taoCONFIG Input File

```
foo = (binary "Hello, world!")
```

#### Resulting JAXN Config Data

```javascript
{
   foo: $48656C6C6F2C20776F726C6421
}
```


## cbor

The `cbor` value extension parses binary data as [CBOR] and returns the resulting value.

#### Example taoCONFIG Input File

```
foo = (cbor $82f5f4)
```

#### Resulting JAXN Config Data

```javascript
{
   foo: [
      true,
      false
   ]
}
```

Note that `cbor` is frequently combined with `read` as in `foo = (cbor (read "filename.cbor"))`.


## copy

The `copy` value extension copies a value

#### Example taoCONFIG Input File

```

```

#### Resulting JAXN Config Data

```javascript
```


## debug

This value extension is a debugging tool and is similar to the `stderr` member extension.

It produces a single string value with the [JSON] representation of the library's internal intermediate data structure for the referenced part of the config data in its current state.

#### Example taoCONFIG Input File

```
foo = 42
bar = (debug foo)
```

#### Resulting JAXN Config Data

```javascript
{
   bar: "{position:\"tests/doc_value_debug.config:1:6\",concat_list:[{clear:true,atom:42}]}",
   foo: 42
}
```


## env

The `env` value extensions obtain the value of an environment variable as string.
For plain `env` it is an error when the environment variable does not exist, the `env?` alternative form returns a default value.

#### Example taoCONFIG Input File

```
foo = (env "USER")
bar = (env? "GRMBLFX" "default")
```

#### Resulting JAXN Config Data

```javascript
{
   bar: "default",
   foo: "colin"
}
```


## jaxn

The `jaxn` value extension parses string data as [JAXN] and returns the resulting value.

#### Example taoCONFIG Input File

```
foo = (jaxn '[Infinity, $ff]')
```

#### Resulting JAXN Config Data

```javascript
{
   foo: [
      Infinity,
      $FF
   ]
}
```

Note that `jaxn` is frequently combined with `string` and `read` as in `foo = (jaxn (string (read "filename.jaxn")))`.


## json

The `json` value extension parses string data as [JSON] and returns the resulting value.

#### Example taoCONFIG Input File

```
foo = (json '["a","b"]')
```

#### Resulting JAXN Config Data

```javascript
{
   foo: [
      "a",
      "b"
   ]
}
```

Note that `json` is frequently combined with `string` and `read` as in `foo = (json (string (read "filename.json")))`.


## msgpack

The `msgpack` value extension parses binary data as [MsgPack] and returns the resulting value.

#### Example taoCONFIG Input File

```
foo = (msgpack $82a161c3a162c2)
```

#### Resulting JAXN Config Data

```javascript
{
   foo: {
      a: true,
      b: false
   }
}
```

Note that `msgpack` is frequently combined with `read` as in `foo = (msgpack (read "filename.msgpack"))`.


## parse

The `parse` value extension parses the given string as a single config value just "as if" the config file contained the string instead of the invocation of `parse`.

#### Example taoCONFIG Input File

```
foo = (parse "null")
```

#### Resulting JAXN Config Data

```javascript
{
   foo: null
}
```

Note that the value described in the string is *not* allowed to use addition/concatenation, however references and/or other value extensions are allowed.


## read

The `read` file extension reads the contents of a file and returns them as binary data.

#### Example taoCONFIG Input File

```
foo = (read "tests/doc_value_read.config")
bar = (string (read "tests/doc_value_read.config"))
```

#### Resulting JAXN Config Data

```javascript
{
   bar: "foo = (read \"tests/doc_value_read.config\")\nbar = (string (read \"tests/doc_value_read.config\"))\n",
   foo: $666F6F203D202872656164202274657374732F646F635F76616C75655F726561642E636F6E66696722290A626172203D2028737472696E67202872656164202274657374732F646F635F76616C75655F726561642E636F6E6669672229290A
}
```

Note that `read` must be combined with `string` in order to validate the data as UTF-8 and transform it into a string.


## shell

The `shell` value extension execute the given string as shell script and returns its output.

#### Example taoCONFIG Input File

```
foo = (shell "uname -s")
```

#### Resulting JAXN Config Data

```javascript
{
   foo: "Darwin\n"
}
```

Note that availability and behaviour of the  `shell` value extension are inherently system dependent.
Currently it is only supported on Unix-style operating system like Linux and macOS.


## split

The `split` value extensions splits a string into its space-separated components and returns an array of them where "space" is a non-empty sequence of `' ', '\n', '\r', '\t', '\v' and/or '\f'` characters.

#### Example taoCONFIG Input File

```
foo = (split "a b c ")
```

#### Resulting JAXN Config Data

```javascript
{
   foo: [
      "a",
      "b",
      "c"
   ]
}
```


## string

The `string` value extension transforms a binary value into a string value.
It validates that the binary data is valid UTF-8 and produces an error if that is not the case.

#### Example taoCONFIG Input File

```
foo = (string $48656C6C6F2C20776F726C6421)
```

#### Resulting JAXN Config Data

```javascript
{
   foo: "Hello, world!"
}
```


## ubjson

The `ubjson` value extension parses binary data as [UBJSON] and returns the resulting value.

#### Example taoCONFIG Input File

```
foo = (ubjson $4344)
```

#### Resulting JAXN Config Data

```javascript
{
   foo: "D"
}
```

Note that `ubjson` is frequently combined with `read` as in `foo = (ubjson (read "filename.ubjson"))`.
Copyright (c) 2018-2020 Dr. Colin Hirsch and Daniel Frey

[CBOR]: http://cbor.io
[JAXN]: https://github.com/stand-art/jaxn
[JSON]: https://tools.ietf.org/html/rfc8259
[MsgPack]: http://msgpack.org
[taoCONFIG]: https://github.com/taocpp/config
[taoJSON]: https://github.com/taocpp/json
[UBJSON]: http://ubjson.org
