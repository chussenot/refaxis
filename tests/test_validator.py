import json
import jsonschema
from jsonschema import validate
import os

# Define the path to the schema file
SCHEMA_FILE = 'schemas/asset_schema.json'

# Define the path to the folder containing JSON files to validate
ASSETS_FOLDER = 'assets'

def validate_assets(schema, assets_folder):
    for filename in os.listdir(assets_folder):
        if filename.endswith('.json'):
            with open(os.path.join(assets_folder, filename), 'r') as file:
                asset_data = json.load(file)
                try:
                    validate(instance=asset_data, schema=schema)
                    print(f"Validation successful for {filename}")
                except jsonschema.exceptions.ValidationError as e:
                    print(f"Validation failed for {filename}: {e}")

def main():
    # Load the schema
    with open(SCHEMA_FILE, 'r') as schema_file:
        schema = json.load(schema_file)

    # Validate the JSON files in the assets folder
    validate_assets(schema, ASSETS_FOLDER)

if __name__ == '__main__':
    main()
