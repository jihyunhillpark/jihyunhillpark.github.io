import { defaultTheme } from '@vuepress/theme-default'
import { head } from './configs/index.js'

export default {
  base: '/',
  head,
  locales: {
    '/': {
      lang: 'en-US',
      title: 'jihyunee blog',
      description: 'jihyun\'s dev&tech blog'
    },
  },
  theme: defaultTheme({
    sidebar: 'auto',
    logo: '/images/author.jpg'
  }),
}
