import pandas as pd
from sodapy import Socrata

meses = ['01','02','03','04','05','06','07','08','09','10','11','12']
años = ['2016','2017','2018']



client = Socrata("www.datos.gov.co", None)

results = client.get("xfif-myr2",fechainscripcionbeneficiario='2016-01-01')

results_df = pd.DataFrame.from_records(results)

for año in años:
    for mes in meses:
        if año == '2016' and mes == '01':
            pass
        results = client.get("xfif-myr2",fechainscripcionbeneficiario=año+'-'+mes+'-01')
        results_df_aux = pd.DataFrame.from_records(results)
        results_df = pd.concat([results_df,results_df_aux],axis=0)


print(results_df)

