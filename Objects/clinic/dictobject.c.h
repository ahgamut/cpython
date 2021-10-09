/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(dict_fromkeys__doc__,
"fromkeys($type, /, iterable, value=None)\n"
"--\n"
"\n"
"Returns a new dict with keys from iterable and values equal to value.");

#define DICT_FROMKEYS_METHODDEF    \
    {"fromkeys", (PyCFunction)dict_fromkeys, METH_FASTCALL|METH_CLASS, dict_fromkeys__doc__},

static PyObject *
dict_fromkeys_impl(PyTypeObject *type, PyObject *iterable, PyObject *value);

static PyObject *
dict_fromkeys(PyTypeObject *type, PyObject **args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"iterable", "value", NULL};
    static _PyArg_Parser _parser = {"O|O:fromkeys", _keywords, 0};
    PyObject *iterable;
    PyObject *value = Py_None;

    if (!_PyArg_ParseStack(args, nargs, kwnames, &_parser,
        &iterable, &value)) {
        goto exit;
    }
    return_value = dict_fromkeys_impl(type, iterable, value);

exit:
    return return_value;
}

PyDoc_STRVAR(dict___contains____doc__,
"__contains__($self, /, key)\n"
"--\n"
"\n"
"True if D has a key k, else False.");

#define DICT___CONTAINS___METHODDEF    \
    {"__contains__", (PyCFunction)dict___contains__, METH_FASTCALL|METH_COEXIST, dict___contains____doc__},

static PyObject *
dict___contains___impl(PyDictObject *self, PyObject *key);

static PyObject *
dict___contains__(PyDictObject *self, PyObject **args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"key", NULL};
    static _PyArg_Parser _parser = {"O:__contains__", _keywords, 0};
    PyObject *key;

    if (!_PyArg_ParseStack(args, nargs, kwnames, &_parser,
        &key)) {
        goto exit;
    }
    return_value = dict___contains___impl(self, key);

exit:
    return return_value;
}
/*[clinic end generated code: output=c6b571bd82b0c879 input=a9049054013a1b77]*/
