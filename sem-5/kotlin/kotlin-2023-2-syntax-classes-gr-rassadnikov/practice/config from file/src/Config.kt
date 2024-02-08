import kotlin.properties.ReadOnlyProperty
import kotlin.reflect.KProperty

class Config @Throws constructor(private val config: String) : ReadOnlyProperty<Any?, String> {
    private val storage: MutableMap<String, String> = hashMapOf()

    init {
        val stream = getResource(config) ?: throw IllegalArgumentException("Can't find resource by config: $config.")
        stream.reader().forEachLine {
            if (!it.contains("=")) throw IllegalArgumentException("Incorrect line in resource.")
            val key = it.substringBefore(" = ").trim()
            val value = it.substringAfterLast(" = ").trim()
            storage[key] = value
        }
    }

    @Throws
    override operator fun getValue(thisRef: Any?, property: KProperty<*>): String {
        val name = property.name
        return storage[name] ?: throw IllegalArgumentException("Can't find value by key: $name.")
    }

    @Throws
    operator fun provideDelegate(thisRef: Any?, property: KProperty<*>): ReadOnlyProperty<Any?, String> {
        val name = property.name
        if (storage[name] == null) throw IllegalArgumentException("Can't find value by key: $name.")
        return this
    }

}
