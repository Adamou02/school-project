import atheris
import sys
import zlib

@atheris.instrument_func
def TestOneInput(data):
  try:
    decompressed = zlib.decompress(data)
  except zlib.error:
    return

  if len(decompressed) < 2:
    return

  try:
    if decompressed.decode() == 'FU':
      raise RuntimeError('Boom')
  except UnicodeDecodeError:
    pass
  

def CustomMutator(data, max_size, seed):
  try:
    decompressed = zlib.decompress(data)
  except zlib.error:
    decompressed = b'Hi'
  else:
    decompressed = atheris.Mutate(decompressed, len(decompressed))
  return zlib.compress(decompressed)


# Configuration et lancement d'Atheris
def main():
    atheris.Setup(sys.argv, TestOneInput, custom_mutator=CustomMutator) # Possibilité d'utiliser des librairies externes de Fuzzing
    print("Fuzzing en cours...")
    atheris.Fuzz()


if __name__ == "__main__":
    main()
