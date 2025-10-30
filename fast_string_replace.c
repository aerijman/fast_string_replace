#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject* replace_at_positions(PyObject* self, PyObject* args) {
    const char* input;
    PyObject* dict_obj;
    Py_ssize_t len;

    // parse (string, dict)
    if (!PyArg_ParseTuple(args, "sO!", &input, &PyDict_Type, &dict_obj))
        return NULL;

    len = strlen(input);
    char* buffer = (char*)malloc(len + 1);
    if (!buffer)
        return PyErr_NoMemory();

    strcpy(buffer, input);

    // iterate through dict items
    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(dict_obj, &pos, &key, &value)) {
        if (!PyLong_Check(key)) {
            free(buffer);
            PyErr_SetString(PyExc_TypeError, "all keys must be integers");
            return NULL;
        }
        if (!PyUnicode_Check(value)) {
            free(buffer);
            PyErr_SetString(PyExc_TypeError, "all values must be strings");
            return NULL;
        }

        Py_ssize_t idx = PyLong_AsSsize_t(key);
        if (idx < 0 || idx >= len) {
            free(buffer);
            PyErr_SetString(PyExc_IndexError, "index out of range");
            return NULL;
        }

        Py_ssize_t ch_len;
        const char* ch_str = PyUnicode_AsUTF8AndSize(value, &ch_len);
        if (ch_str == NULL) {
            free(buffer);
            return NULL;
        }

        if (ch_len != 1) {
            free(buffer);
            PyErr_SetString(PyExc_ValueError, "each replacement must be a single character");
            return NULL;
        }

        buffer[idx] = ch_str[0];
    }

    PyObject* result = PyUnicode_FromString(buffer);
    free(buffer);
    return result;
}

static PyMethodDef Methods[] = {
    {
        "replace_at_positions",
        replace_at_positions,
        METH_VARARGS,
        PyDoc_STR(
            "change_chars(s: str, replacements: dict[int, str]) -> str\n"
            "\n"
            "Return a new string where multiple characters have been replaced.\n"
            "\n"
            "Arguments:\n"
            "  s            -- the original string\n"
            "  replacements -- a dictionary mapping indices to replacement characters\n"
            "\n"
            "Example:\n"
            "  >>> import fast_string_replace\n"
            "  >>> fast_string_replace.replace_at_positions('hello world', {1: 'a', 7: 'W'})\n"
            "  'hallo World'\n"
        )
    },
    {NULL, NULL, 0, NULL}
};





static struct PyModuleDef fast_string_replacemodule = {
    PyModuleDef_HEAD_INIT,
    "fast_string_replace",
    NULL,
    -1,
    Methods
};

PyMODINIT_FUNC PyInit_fast_string_replace(void) {
    return PyModule_Create(&fast_string_replacemodule);
}

