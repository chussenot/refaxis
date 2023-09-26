.PHONY: validate

validate:
	poetry run python -m tests.test_validator

install:
	poetry install

test:
	poetry run pytest
