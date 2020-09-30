# simdjsonTest
Simple C++ project using the [simdjson](https://github.com/simdjson/simdjson) library to parse all json files in a directory and measure the time taken.

This is a POC project created as I was evaluating faster alternatives for parsing json files. Using standard .NET json parsing stuff works great most of the time, but in this particular scenario I had to parse some ten thousand large (30MB+) files.

The json files are assumed to have a root object with at least a `count` numeric property like this:

```json
{
  "count": 100
}
```

On my test machine, using the AVX2 implementation from simdjson, it takes about 2.5 seconds to parse the sample directory comprised of 33 files (total of 933MB).
