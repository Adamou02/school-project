import random
import string
import atheris
import sys
import json

# 1. Fonction qui attend un objet JSON et le traite
def json_parser(data):
    try:
        # Tenter de charger les données en JSON
        json_data = json.loads(data.decode('utf-8'))
        
        # Supposons que nous attendons un objet avec une clé "valeur" qui est un entier
        if "valeur" in json_data:
            valeur = json_data["valeur"]
            # Imaginons une opération sur cet entier
            print(f"Valeur extraite: {valeur}")
            if valeur == 0:
                raise ValueError("Valeur ne peut pas être 0 pour cette opération")
        else:
            raise ValueError("Clé 'valeur' manquante dans l'objet JSON")
        
    except json.JSONDecodeError:
        print("Erreur de parsing JSON : données malformées.")
    except ValueError as e:
        print(f"Erreur de valeur : {e}")
    except Exception as e:
        print(f"Erreur inattendue : {e}")


# 4. Fonction principale pour exécuter les tests
def test_input(data):
    fdp = atheris.FuzzedDataProvider(data)
    
    # Générer un objet JSON aléatoire en utilisant les données fuzzées
    json_data = {
        "valeur": fdp.ConsumeInt(4),  # Utiliser un entier de 32 bits
        "nom": ''.join(random.choices(string.ascii_lowercase, k=fdp.ConsumeInt(1) % 20)),  # Générer un nom aléatoire
        "actif": fdp.ConsumeBool(),  # Ajouter un booléen aléatoire
# ConsumeUnicode(); ConsumeString(); ConsumeIntInRange(); ConsumeIntList(); ConsumeIntListInRange(); ConsumeProbability()

    }
    
    # Convertir en JSON
    json_str = json.dumps(json_data)

    # Tester le parsing du JSON
    json_parser(json_str.encode('utf-8'))


# Configuration et lancement d'Atheris
def main():
    atheris.Setup([sys.argv[0], "-runs=100"], test_input)
    print("Fuzzing en cours...")
    atheris.Fuzz()


if __name__ == "__main__":
    main()
