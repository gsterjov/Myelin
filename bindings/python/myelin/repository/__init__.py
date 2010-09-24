

import sys
from myelin.importer import RepositoryImporter

sys.meta_path.append (RepositoryImporter ('myelin.repository'))
