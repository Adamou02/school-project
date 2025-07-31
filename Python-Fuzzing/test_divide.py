import atheris
import sys


# 1. Fonction de division - Vérifie les inputs pour éviter une division par zéro
def divide(data):
    if len(data) < 2:
        return  # Ignore les inputs trop courts

    a = data[0]
    b = data[1]

    if b == 0:
        raise ValueError("Division par zéro détectée")
    if a is None or b is None:
        raise TypeError("Valeur null détectée dans la division")
    
    return a / b


# # 2. Fonction de parseur JSON - Teste des inputs JSON valides et invalides
# def json_parser(data):
#     try:
#         # Essaie de charger la chaîne comme JSON
#         json.loads(data.decode("utf-8"))
#     except json.JSONDecodeError:
#         pass  # Le fuzzing est utile pour trouver des cas problématiques


# # 3. Fonction de manipulation de chaînes - Identifie des cas spécifiques
# def string_manipulation(data):
#     input_str = data.decode("utf-8", errors="ignore")  # Gère les erreurs d'encodage
#     if "FUZZ" in input_str and len(input_str) > 10:
#         raise RuntimeError("Mot clé dangereux trouvé dans une chaîne longue")
    

# 4. Fonction principale pour exécuter les tests
def test_input(data):
    # Split input data into chunks for testing multiple functions
    if len(data) < 2:
        return

    try:
        # Test sur la fonction de division
        divide(data)

        # Test sur le parseur JSON
        # json_parser(data)

        # Test sur la manipulation de chaînes
        # string_manipulation(data)
    except Exception as e:
        print(f"Crash détecté : {e}")


# Configuration et lancement d'Atheris
def main():
    atheris.Setup([sys.argv[0], "-runs=100"], test_input)
    print("Fuzzing en cours...")
    atheris.Fuzz()


if __name__ == "__main__":
    main()
