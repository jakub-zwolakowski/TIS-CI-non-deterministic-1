#!/bin/bash
tis-analyzer --interpreter -tis-config-load tis.config -tis-config-select 1 -info-json-results test1.json
tis-analyzer --interpreter -tis-config-load tis.config -tis-config-select 2 -info-json-results test2.json
