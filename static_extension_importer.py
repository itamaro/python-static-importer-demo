from importlib._bootstrap import spec_from_loader, _call_with_frames_removed
import _imp
import static_utils

class StaticExtensionImporter:
    _ORIGIN = "static-extension"

    @classmethod
    def find_spec(cls, fullname, path, target=None):
        """
        Use fullname to look up the PyInit function in the main binary. Returns None if not present.
        This allows importing CExtensions that have been statically linked in.
        """

        if not fullname:
            return None
        if not static_utils.check_module(fullname):
            return None
        return spec_from_loader(fullname, cls, origin=cls._ORIGIN)

    @staticmethod
    def create_module(spec):
        """Create a built-in module"""
        return _call_with_frames_removed(static_utils.create_module, spec)

    @staticmethod
    def exec_module(module):
        """Exec a built-in module"""
        _call_with_frames_removed(_imp.exec_builtin, module)

    @classmethod
    def get_code(cls, fullname):
        """Return None as built-in modules do not have code objects."""
        return None

    @classmethod
    def get_source(cls, fullname):
        """Return None as built-in modules do not have source code."""
        return None

    @classmethod
    def is_package(cls, fullname):
        """Return False as built-in modules are never packages."""
        return False
