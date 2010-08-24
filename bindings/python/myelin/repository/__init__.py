

import sys
from ..importer import RepositoryImporter

sys.meta_path.append (RepositoryImporter ('myelin.repository'))
