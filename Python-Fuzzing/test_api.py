import atheris
import sys

with atheris.instrument_imports():  # instrument_imports(include=[], exclude=[])
    import api_utils  # Instrumentation de api_utils 


def get_gender(name):
    api_utils.reach_api("gender", {"name": str(name)})


# 4. Fonction principale pour exécuter les tests
def test_input(data):
    # Split input data into chunks for testing multiple functions
    if len(data) < 2:
        return

    try:
        # Test sur les appels API
        get_gender(data)
    except Exception as e:
        print(f"Crash détecté : {e}")


# Configuration et lancement d'Atheris
def main():
    atheris.Setup([sys.argv[0], "-runs=100"], test_input)
    print("Fuzzing en cours...")
    atheris.Fuzz()


if __name__ == "__main__":
    main()
