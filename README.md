# Json-Formatter
A command line JSON formatter for linux.

## Dependency
jansson 2.10 -> https://github.com/akheron/jansson/tree/2.10

*dependency is managed as a submodule to the project.*

## Usage
  ```
  $ jsonf   <filename>
  
  Usage:  [options] <Input filename> <Input filename>..
  Options:
    -o <filename>   output filename
    -n <# of char>  indent size
```

# Other Json Formatter
jq is a lightweight and flexible command-line JSON processor.

http://stedolan.github.io/jq/

jq is like sed for JSON data – you can use it to slice and filter and map and transform structured data with the same ease that sed, awk, grep and friends let you play with text.

jq is written in portable C, and it has zero runtime dependencies. You can download a single binary, scp it to a far away machine, and expect it to work.

*Information source:* https://stackoverflow.com/questions/5243885/json-command-line-formatter-tool-for-linux
