#!/usr/bin/env python3
"""One correct implementation of "find the calls to F in this C source".

Written after writing FOUR separate call-site appliers in a day and getting
the same details wrong in three of them. Every sweep in this tree needs the
same four things, and each is a trap:

  1. COMMENTS must be excluded, but WITHOUT MOVING OFFSETS. The headers here
     quote call sites constantly - deleting comments makes a grep count the
     documentation, and blanking them to spaces is the only way an offset
     computed on the stripped text still indexes the real file.
  2. ARGUMENTS end at the MATCHING paren, not the first ')' and not the end
     of the line. Multi-line calls are common, and so are nested calls.
  3. ARGUMENTS split at depth zero. Foo(a, g(b, c)) has two, not three.
  4. A DECLARATION LOOKS EXACTLY LIKE A CALL. This is the one that keeps
     biting. Definitions are easy - a '{' follows the closing paren - but a
     declaration ends in ';' just like a call statement, and the only thing
     that distinguishes it is the RETURN TYPE in front of the name. Miss it
     and a sweep rewrites prototypes into nonsense like
         void TreeLowerBound(void *scratch,&g_valueGuardMap);
     which is exactly what happened, twice, in one day.

Use classify() and act only on kind == 'call'.
"""
import re

# A declaration is distinguished from a call ONLY by the return type in front
# of the name.  Two things this must get right, both learned the hard way:
#
#  * the return type is not one word.  "void __fastcall f();" and
#    "unsigned char *f();" are declarations, and a pattern allowing a single
#    identifier calls them both CALLS -- which silently skips them during a
#    prototype sweep, leaving a K&R-empty declaration in place.  That is the
#    worst possible outcome, because a K&R prototype accepts any argument
#    list, so the call sites then compile clean no matter how wrong they are.
#  * a C keyword is not a return type.  "return f(a);" ends with an
#    identifier and whitespace exactly like "int f(a)", so without a keyword
#    blacklist every `return f(...)` call site is classified as a DECLARATION
#    and skipped by every sweep that acts on calls.
KEYWORDS = {'return', 'if', 'while', 'for', 'switch', 'do', 'else', 'case',
            'sizeof', 'goto', 'break', 'continue', 'default', 'typedef'}

# [\s*]+ rather than \s+ so a pointer return type whose star binds to the
# NAME -- "unsigned char *f();" -- still ends the type correctly.
DECL = re.compile(r'(?:^|[;{}])\s*(?:static\s+|extern\s+|const\s+)*'
                  r'((?:[A-Za-z_]\w*[\s*]+)+)$')


def _is_declaration(before):
    m = DECL.search(before)
    if not m:
        return False
    words = re.findall(r'[A-Za-z_]\w*', m.group(1))
    return bool(words) and not (set(words) & KEYWORDS)


def blank_comments(src):
    """Comments replaced by spaces - every offset stays a real file offset."""
    src = re.sub(r'/\*.*?\*/', lambda m: ' ' * (m.end() - m.start()), src, flags=re.S)
    return re.sub(r'//[^\n]*', lambda m: ' ' * (m.end() - m.start()), src)


def split_args(text):
    """Split at parenthesis depth zero. Returns [] for an empty list."""
    args, depth, cur = [], 0, ''
    for ch in text:
        if ch == '(':
            depth += 1
        elif ch == ')':
            depth -= 1
        if ch == ',' and depth == 0:
            args.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip() or args:
        args.append(cur.strip())
    return [a for a in args if a]


def find(src, name, blanked=None):
    """Yield dicts for every occurrence of `name(` in src.

    src      the ORIGINAL text (offsets refer to it)
    blanked  optional pre-blanked copy, to avoid re-blanking per name

    keys: start, open, close, end, args, kind
      start .. offset of the name
      open  .. offset just after '('
      close .. offset of the matching ')'
      end   .. offset just after that ')'
      kind  .. 'call' | 'definition' | 'declaration'
    """
    b = blank_comments(src) if blanked is None else blanked
    for m in re.finditer(r'\b%s\s*\(' % re.escape(name), b):
        depth, j = 1, m.end()
        while depth and j < len(b):
            if b[j] == '(':
                depth += 1
            elif b[j] == ')':
                depth -= 1
            j += 1
        close = j - 1
        after = b[j:].lstrip()
        if after.startswith('{'):
            kind = 'definition'
        elif _is_declaration(b[:m.start()]):
            kind = 'declaration'
        else:
            kind = 'call'
        yield {'start': m.start(), 'open': m.end(), 'close': close, 'end': j,
               'args': split_args(b[m.end():close]), 'kind': kind}


def calls(src, name, blanked=None):
    """Only the real call sites."""
    return [c for c in find(src, name, blanked) if c['kind'] == 'call']
