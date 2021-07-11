from typing import Any
from typing import Optional
from _markupsafe_speedups import (
    escape as _escape,
    escape_silent as _escape_silent,
    soft_str as _soft_str,
    soft_unicode as _soft_unicode,
)
from . import Markup


def escape(s: Any) -> Markup:
    return _escape(s)


def escape_silent(s: Optional[Any]) -> Markup:
    return _escape_silent(s)


def soft_str(s: Any) -> str:
    return _soft_str(s)


def soft_unicode(s: Any) -> str:
    return _soft_unicode(s)
