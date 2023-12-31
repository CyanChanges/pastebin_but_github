import { Loader } from "@koishijs/loader";
import { Context } from "koishi";

function insertKey(object: {}, temp: {}, rest: string[]) {
  for (const key of rest) {
    temp[key] = object[key]
    delete object[key]
  }
  Object.assign(object, temp)
}

function splitPath(path: string) {
  return path.split(/\/?(@[~\w-]+\/[~\w:-]+|[~\w:-]+)\/?/).filter(Boolean)
}

function rename(object: any, old: string, neo: string, value: any) {
  const keys = Object.keys(object)
  const index = keys.findIndex(key => key === old || key === '~' + old)
  const rest = index < 0 ? [] : keys.slice(index + 1)
  const temp = { [neo]: value }
  delete object[old]
  delete object['~' + old]
  insertKey(object, temp, rest)
}

export class K2ConfigWriter {
  protected loader: Loader

  constructor(protected ctx: Context) {
    this.loader = this.ctx.loader
  }

  async reload(path: string, config: any, newKey?: string) {
    let [parent, oldKey] = this.resolve(path)
    oldKey = oldKey.startWith('~') ? oldKey.substring(1, Infinity) : oldKey
    if (newKey) {
      await this.loader.unloadPlugin(parent.ctx, oldKey)
    }
    await this.loader.reloadPlugin(parent.ctx, newKey || oldKey, config)
    rename(parent.config, oldKey, newKey || oldKey, config)
    await this.loader.writeConfig()
  }

  getGroup(plugins: any, ctx: Context) {
    const result = { ...plugins }
    for (const key in plugins) {
      if (key.startsWith('$')) continue
      const value = plugins[key]
      const name = key.split(':', 1)[0].replace(/^~/, '')

      // handle plugin groups
      if (name === 'group') {
        const fork = ctx.scope[Loader.kRecord][key]
        if (!fork) continue
        result[key] = this.getGroup(value, fork.ctx)
      }
    }
    return result
  }

  async get() {
    const result = { ...this.loader.config }
    result.plugins = this.getGroup(result.plugins, this.loader.entry)
    return result
  }

  resolve(path: string) {
    const segments = splitPath(path)
    if (path.endsWith('/')) segments.push('')
    let ctx = this.loader.entry
    let name = segments.shift()
    while (segments.length) {
      ctx = ctx.scope[Loader.kRecord][name].ctx
      name = segments.shift()
    }
    return [ctx.scope, name] as const
  }

  async unload(path: string, config = {}, newKey?: string) {
    const [parent, oldKey] = this.resolve(path)
    this.loader.unloadPlugin(parent.ctx, oldKey)
    rename(parent.config, oldKey, '~' + (newKey || oldKey), config)
    await this.loader.writeConfig()
  }

  async remove(path: string) {
    const [parent, key] = this.resolve(path)
    this.loader.unloadPlugin(parent.ctx, key)
    delete parent.config[key]
    delete parent.config['~' + key]
    await this.loader.writeConfig()
  }
}
