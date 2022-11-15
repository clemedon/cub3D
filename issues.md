
#           CUB3D - ISSUES

>       help

## Guide

Issues should look like commits:
    <type>(<optional_scope>): My commit message title
    My commit message body

**TYPE**:

*style*     changes that doesnt affect the code (typo, norm...)
*docs*      changes to the documentation
*build*     changes to the build
*chore*     changes that dont involve production code change (config)

*feat*      creation of a new feature
*test*      creation of tests
*fix*       fix a bug
*refactor*  code changes that is not a feat neither a fix

**OPTIONAL SCOPE**: anything relevant
**TITLE**: Summary, *imperative*, start upper case, don't end with a period.
**BODY**: *What* and *why* (not *how*). 72 chars max.

Example: `chore: Update issues`

## Issues

# ―――――――→ athirion ←―――――――

# ――――――――→ cvidon ←――――――――

docs(help): Fix 'recovery' chapter

build: Fix libmlx-linux for mac
- Try to include X11 in cub3d.h in addition to -I

refactor: Add constants.h, a private header

feat: Conditional statement in the code for OS compatibility

refactor: Turn define into enum when it is possible

# ――――――――――→ ?? ←――――――――――

## Archive (newer to older)

feat: Add cub init

fix(exit): Clean exit
- exit cub3d without any leaks

test: Draw border and cross

feat(window): Create a window
- window should be close with escape
