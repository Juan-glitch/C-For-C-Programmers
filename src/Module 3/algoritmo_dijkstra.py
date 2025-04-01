# Importamos el módulo heapq que nos permite usar una "cola de prioridad".
# Esto es como una lista mágica que siempre nos da el elemento más pequeño.
import heapq
import math  # Para usar "math.inf" que representa un número infinito

def dijkstra(graph, start):
    """
    Esta función encuentra el camino más corto desde un punto de partida a todos los demás puntos del "mapa".

    Parámetros:
      - graph: Es un diccionario que representa nuestro mapa. Cada llave es una "ciudad" (por ejemplo, 'A', 'B', etc.)
               y el valor es una lista de caminos directos que salen de esa ciudad. 
               Cada camino se representa como una tupla: (ciudad_vecina, distancia).
      - start: Es la ciudad donde empiezas el viaje (por ejemplo, 'A').

    Devuelve:
      - Un diccionario "distance" donde se muestra la distancia más corta desde la ciudad de inicio
        a cada una de las otras ciudades.
    """

    # Paso 1: Inicializar las distancias
    # Creamos un diccionario "distance" para guardar la distancia desde la ciudad de inicio a cada ciudad.
    # Al principio, ponemos todas las distancias como "infinito" (no sabemos cuánto tardarás en llegar allí)
    # excepto para la ciudad de inicio, que es 0 porque ya estás allí.
    distance = {node: math.inf for node in graph}
    distance[start] = 0  # La distancia de A a A es 0

    # Paso 2: Crear la cola de prioridad
    # La cola de prioridad es una lista especial que nos ayuda a elegir siempre la ciudad que está más cerca.
    # Cada elemento en la cola es una tupla: (distancia, ciudad)
    # Comenzamos con la ciudad de inicio, con una distancia de 0.
    queue = [(0, start)]
    
    # Paso 3: Explorar el mapa
    # Mientras haya ciudades en la cola, seguimos buscando la ruta más corta.
    while queue:
        # Sacamos de la cola la ciudad que tiene la distancia más corta (la que está más cerca)
        current_distance, current_city = heapq.heappop(queue)
        
        # Si ya encontramos una forma más rápida de llegar a esta ciudad, la ignoramos.
        if current_distance > distance[current_city]:
            continue
        
        # Paso 4: Revisar los caminos desde la ciudad actual
        # Para cada camino directo (vecino) desde la ciudad actual:
        for neighbor, weight in graph[current_city]:
            # Calculamos la nueva distancia sumando la distancia actual y la distancia del camino al vecino.
            new_distance = current_distance + weight
            
            # Si la nueva distancia es menor que la distancia que ya teníamos para llegar a ese vecino...
            if new_distance < distance[neighbor]:
                # Actualizamos la distancia para ese vecino.
                distance[neighbor] = new_distance
                # Y agregamos este vecino a la cola para poder explorar sus caminos después.
                heapq.heappush(queue, (new_distance, neighbor))
    
    # Paso 5: Cuando ya no hay más ciudades en la cola, devolvemos las distancias.
    # Esto significa que ya sabemos la distancia más corta desde el inicio a cada ciudad.
    return distance

# --- EJEMPLO PRÁCTICO ---
# Imagina que tenemos un mapa sencillo de ciudades (representadas con letras):
# 'A', 'B', 'C' y 'D'. El mapa se representa con un diccionario.
# Cada ciudad tiene una lista de caminos directos hacia otras ciudades, y cada camino tiene una "distancia".

graph_example = {
    'A': [('B', 5), ('C', 2)],  # Desde A, puedes ir a B (distancia 5) o a C (distancia 2)
    'B': [('A', 5), ('C', 1), ('D', 3)],  # Desde B, puedes ir a A, C o D
    'C': [('A', 2), ('B', 1), ('D', 7)],  # Desde C, puedes ir a A, B o D
    'D': [('B', 3), ('C', 7)]   # Desde D, puedes ir a B o a C
}

# Queremos saber cuál es la distancia más corta para llegar desde la ciudad 'A' a todas las demás.
result = dijkstra(graph_example, 'A')

# Mostramos el resultado.
# Esto imprimirá la distancia más corta desde 'A' a cada ciudad en nuestro mapa.
print("Distancias más cortas desde la ciudad 'A':")
for city, dist in result.items():
    print(f"Ciudad {city}: {dist}")

# Resultado esperado:
# Ciudad A: 0        (porque es el punto de partida)
# Ciudad B: 3        (porque el camino A -> C -> B es 2 + 1 = 3, que es mejor que A -> B que es 5)
# Ciudad C: 2
# Ciudad D: 6        (porque el camino A -> C -> B -> D es 2 + 1 + 3 = 6)
# --- FIN DEL EJEMPLO ---
# Este código es un ejemplo de cómo funciona el algoritmo de Dijkstra.
# Puedes cambiar el mapa y las distancias para probar diferentes escenarios.
# Recuerda que este algoritmo es muy útil para encontrar la ruta más corta en mapas, como los de navegación.
# También se puede usar en redes de computadoras, juegos y muchas otras aplicaciones.
# ¡Espero que esto te haya ayudado a entender cómo funciona el algoritmo de Dijkstra!
# Recuerda que la programación es como resolver un rompecabezas.
# Cada pieza tiene su lugar y al final, todo encaja.
# ¡Diviértete programando!
# Fin del código
