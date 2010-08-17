

import sys
from ..importer import MetaImporter

sys.meta_path.append (MetaImporter ('myelin.meta'))
