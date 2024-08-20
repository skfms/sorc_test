
# Basic
  + 4-column indent.
  + Opening curly on same line as keyword, if possible, otherwise line up.
  + Space before the opening curly of a multi-line BLOCK.
  + One-line BLOCK may be put on one line, including curlies.
  + No space before the semicolon.
  + Semicolon omitted in "short" one-line BLOCK.
  + Space around most operators.
  + Space around a "complex" subscript (inside brackets).
  + Blank lines between chunks that do different things.
  + Uncuddled elses.
  + No space between function name and its opening parenthesis.
  + Space after each comma.
  + Long lines broken after an operator (except and and or).
  + Space after last parenthesis matching on current line.
  + Line up corresponding items vertically.
  + Omit redundant punctuation as long as clarity doesn't suffer.

```
open(my $fh, '<', $foo) || die "Can't open $foo: $!";
die "Can't open $foo: $!" unless open(my $fh, '<', $foo);

print "Starting analysis\n" if $verbose;
$verbose && print "Starting analysis\n";
```

# Spacing and syntax usage
###
  + (O) if (cond) {
  + (O) while (cond) {
  + (X) if(cond) {
  + (X) if (cond){
  + (X) if(cond){
###
  + (O) func(params)
  + (X) func (params)
###
  + (O) my $list = [ 1, 2, 3 ];
  + (O) my $hash = { one => 1, two => 2 };
###
  + (O) !$foo
  + (X) ! $foo
  + (O) $foo->{text}
  + (O) $foo{text}
  + (O) $foo->[index]
  + (O) $foo[index]
  + (O) $foo->(index)
  + (X) &$foo(args)
  + (X) & $foo(args)
###
  + (O) a + b
  + (X) a+b
  + (O) a*3 + b*4
  + (X) a+3 * b+4

```
if (expr) 
{
    code();
} 
else 
{
    code();
}

if (    $arg1->{foo}->{bar}
     && $arg2 * $arg1->{xzy} > $arg3->{baz}
     && $arg3->{more}
   ) 
{
  code();
}
```

```
description => "Enable backup fleecing. Cache backup data from blocks where new guest writes happen"
    ." on specified storage instead of copying them directly to the backup target. This can help"
    ." guest IO performance and even prevent hangs, at the cost of requiring more storage space.";
```

